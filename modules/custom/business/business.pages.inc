<?php

/**
 * @file
 * Page callbacks for adding, editing and deleting businesses.
 */

/**
 * Page callback: Returns the business add/edit form to add a new business.
 *
 * @see business_edit_form()
 *
 * @param object $business_type
 *   The type of business to create.
 *
 * @return array
 *   The business add/edit form render array.
 */
function business_add_page($business_type) {
  $business = entity_create('business', array('type' => $business_type->type));

  return drupal_get_form('business_edit_form', $business);
}

/**
 * Page callback: Returns the business add/edit form to edit an existing
 * business.
 *
 * @see business_edit_form()
 *
 * @param object $business
 *   The business to edit.
 *
 * @return array
 *   The business add/edit form render array.
 */
function business_edit_page(Business $business) {
  drupal_set_title(t('Edit business %business', array('%business' => $business->name)), PASS_THROUGH);

  return drupal_get_form('business_edit_form', $business);
}

/**
 * Form constructor for the business add/edit form.
 *
 * @param Business $business
 *   The business that is being added/edited.
 *
 * @ingroup forms
 */
function business_edit_form($form, &$form_state, Business $business) {
  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['business'])) {
    $form_state['business'] = $business;
  }
  else {
    $business = $form_state['business'];
  }

  // Business name.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Business name'),
    '#required' => TRUE,
    '#default_value' => !empty($business->name) ? $business->name : '',
    '#maxlength' => 255,
    '#weight' => -5,
  );

  // Attach all form elements for the fields.
  field_attach_form('business', $business, $form, $form_state, entity_language('business', $business));

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('business_edit_form_submit'),
  );

  if (!empty($business->bid) && business_access('delete', $business)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('business_edit_form_delete_submit'),
    );
  }

  return $form;
}

/**
 * Form validation handler for business_edit_form().
 */
function business_edit_form_validate($form, &$form_state) {
  field_attach_form_validate('business', $form_state['business'], $form, $form_state);
}

/**
 * Form submission handler for business_edit_form().
 *
 * Saves a business and outputs a status message to the user.
 */
function business_edit_form_submit($form, &$form_state) {
  $business = $form_state['business'];
  entity_form_submit_build_entity('business', $business, $form, $form_state);

  $operation = !empty($business->is_new) ? 'add' : 'edit';

  if (business_save($business)) {
    $message = $operation == 'add' ? 'New business %name has been added.' : 'The changes have been saved.';
    drupal_set_message(t($message, array('%name' => $business->name)));
  }
  else {
    drupal_set_message(t('The business could not be saved.'), 'error');
    watchdog('business', 'Business %name could not be saved.', array('%name' => $business->name), WATCHDOG_ERROR);
  }
}

/**
 * Form submission handler for business_edit_form().
 *
 * Handles the 'Delete' button on the node form.
 *
 * @see business_edit_form()
 * @see business_delete_confirm_form()
 */
function business_edit_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $business = $form_state['business'];
  $form_state['redirect'] = array('business/' . $business->bid . '/delete', array('query' => $destination));
}

/**
 * Form constructor for the business deletion confirmation form.
 *
 * @see business_delete_confirm_form_submit()
 */
function business_delete_confirm_form($form, &$form_state, Business $business) {
  $form_state['business'] = $business;
  return confirm_form($form,
    t('Are you sure you want to delete %name?', array('%name' => $business->name)),
    'business/' . $business->bid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for business_delete_confirm_form().
 *
 * Deletes the business.
 *
 * @see business_delete_confirm_form()
 */
function business_delete_confirm_form_submit($form, &$form_state) {
  $business = $form_state['business'];
  business_delete($business);
  drupal_set_message(t('Business %name has been deleted.', array('%name' => $business->name)));
  $form_state['redirect'] = '<front>';
}

/**
 * Page callback for the business page.
 */
function business_detail_page($business) {
  drupal_set_title($business->name);
  $output = entity_view($business->type, array($business));

  // Prevent the business title from being rendered twice.
  $output['business'][$business->bid]['#page'] = TRUE;

  return $output;
}

