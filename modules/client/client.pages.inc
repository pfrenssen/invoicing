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
 * @param object $client_type
 *   The type of client to create.
 *
 * @return array
 *   The client add/edit form render array.
 */
function client_add_page($client_type) {
  $client = entity_create('client', array('type' => $client_type->type));

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
}

/**
 * Form submission handler for client_edit_form().
 *
 * Saves a client.
 */
function client_edit_form_submit($form, &$form_state) {
  $client = $form_state['client'];
  entity_form_submit_build_entity('client', $client, $form, $form_state);
  client_save($client);
}

/**
 * Form submission handler for client_edit_form().
 *
 * Deletes a client.
 */
function client_edit_form_delete_submit($form, &$form_state) {
  // @todo Implement.
  var_dump(__FUNCTION__); die;
}
