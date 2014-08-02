<?php

/**
 * @file
 * Page callbacks for adding, editing and deleting clients.
 */

/**
 * Page callback: Returns the client add/edit form to add a new client.
 *
 * @see client_edit_form()
 *
 * @return array
 *   The client add/edit form render array.
 */
function client_add_page() {
  $client = client_create();

  return drupal_get_form('client_edit_form', $client);
}

/**
 * Page callback: Returns the client add/edit form to edit an existing client.
 *
 * @see client_edit_form()
 *
 * @param object $client
 *   The client to edit.
 *
 * @return array
 *   The client add/edit form render array.
 */
function client_edit_page(Client $client) {
  drupal_set_title(t('Edit client %client', array('%client' => $client->name)), PASS_THROUGH);

  return drupal_get_form('client_edit_form', $client);
}

/**
 * Form constructor for the client add/edit form.
 *
 * @param Client $client
 *   The client that is being added/edited.
 *
 * @ingroup forms
 */
function client_edit_form($form, &$form_state, Client $client) {
  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['client'])) {
    $form_state['client'] = $client;
  }
  else {
    $client = $form_state['client'];
  }

  // Client name.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Client name'),
    '#required' => TRUE,
    '#default_value' => !empty($client->name) ? $client->name : '',
    '#maxlength' => 255,
    '#weight' => -5,
  );

  // Attach all form elements for the fields.
  field_attach_form('client', $client, $form, $form_state, entity_language('client', $client));

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('client_edit_form_submit'),
  );

  if (!empty($client->cid) && client_access('delete', $client)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('client_edit_form_delete_submit'),
    );
  }

  return $form;
}

/**
 * Form validation handler for client_edit_form().
 */
function client_edit_form_validate($form, &$form_state) {
  field_attach_form_validate('client', $form_state['client'], $form, $form_state);
}

/**
 * Form submission handler for client_edit_form().
 *
 * Saves a client and outputs a status message to the user.
 */
function client_edit_form_submit($form, &$form_state) {
  $client = $form_state['client'];
  entity_form_submit_build_entity('client', $client, $form, $form_state);

  $operation = !empty($client->is_new) ? 'add' : 'edit';

  if (client_save($client)) {
    $message = $operation == 'add' ? 'New client %name has been added.' : 'The changes have been saved.';
    // @codingStandardsIgnoreStart
    drupal_set_message(t($message, array('%name' => $client->name)));
    // @codingStandardsIgnoreEnd
  }
  else {
    drupal_set_message(t('The client could not be saved.'), 'error');
    watchdog('client', 'Client %name could not be saved.', array('%name' => $client->name), WATCHDOG_ERROR);
  }

  $form_state['redirect'] = 'clients';
}

/**
 * Form submission handler for client_edit_form().
 *
 * Handles the 'Delete' button on the node form.
 *
 * @see client_edit_form()
 * @see client_delete_confirm_form()
 */
function client_edit_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $client = $form_state['client'];
  $form_state['redirect'] = array('client/' . $client->cid . '/delete', array('query' => $destination));
}

/**
 * Form constructor for the client deletion confirmation form.
 *
 * @see client_delete_confirm_form_submit()
 */
function client_delete_confirm_form($form, &$form_state, Client $client) {
  $form_state['client'] = $client;
  return confirm_form($form,
    t('Are you sure you want to delete %name?', array('%name' => $client->name)),
    'client/' . $client->cid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for client_delete_confirm_form().
 *
 * Deletes the client.
 *
 * @see client_delete_confirm_form()
 */
function client_delete_confirm_form_submit($form, &$form_state) {
  $client = $form_state['client'];
  client_delete($client);
  drupal_set_message(t('Client %name has been deleted.', array('%name' => $client->name)));
  $form_state['redirect'] = 'clients';
}

/**
 * Page callback for the client page.
 */
function client_detail_page($client) {
  drupal_set_title($client->name);
  $output = entity_view($client->type, array($client));

  // Prevent the client title from being rendered twice.
  $output['client'][$client->cid]['#page'] = TRUE;

  return $output;
}
