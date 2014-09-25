<?php

/**
 * @file
 * Page callbacks for adding, editing and deleting tax rates.
 */

/**
 * Page callback: Create a new tax rate.
 */
function tax_rate_add_page() {
  $tax_rate = entity_create('tax_rate', array());

  return drupal_get_form('tax_rate_edit_form', $tax_rate);
}

/**
 * Form constructor for the tax rate add/edit form.
 *
 * @param TaxRate $tax_rate
 *   The tax rate that is being added/edited.
 *
 * @ingroup forms
 */
function tax_rate_edit_form($form, &$form_state, TaxRate $tax_rate) {
  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['tax_rate'])) {
    $form_state['tax_rate'] = $tax_rate;
  }
  else {
    $tax_rate = $form_state['tax_rate'];
  }

  // Attach all form elements for the fields.
  field_attach_form('tax_rate', $tax_rate, $form, $form_state, entity_language('tax_rate', $tax_rate));

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('tax_rate_edit_form_submit'),
  );

  if (!empty($tax_rate->tid) && tax_rate_access('delete', $tax_rate)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('tax_rate_edit_form_delete_submit'),
    );
  }

  return $form;
}

/**
 * Form validation handler for tax_rate_edit_form().
 */
function tax_rate_edit_form_validate($form, &$form_state) {
  field_attach_form_validate('tax_rate', $form_state['tax_rate'], $form, $form_state);
}

/**
 * Form submission handler for tax_rate_edit_form().
 *
 * Saves a tax rate and outputs a status message to the user.
 */
function tax_rate_edit_form_submit($form, &$form_state) {
  $tax_rate = $form_state['tax_rate'];
  entity_form_submit_build_entity('tax_rate', $tax_rate, $form, $form_state);

  $operation = !empty($tax_rate->is_new) ? 'add' : 'edit';

  if (tax_rate_save($tax_rate)) {
    $message = $operation == 'add' ? 'New tax rate has been added.' : 'The changes have been saved.';
    // @codingStandardsIgnoreStart
    drupal_set_message(t($message));
    // @codingStandardsIgnoreEnd
  }
  else {
    drupal_set_message(t('The tax rate could not be saved.'), 'error');
    watchdog('tax_rate', 'Tax rate could not be saved.', WATCHDOG_ERROR);
  }
}

/**
 * Form submission handler for tax_rate_edit_form().
 *
 * Handles the 'Delete' button on the node form.
 *
 * @see tax_rate_edit_form()
 * @see tax_rate_delete_confirm_form()
 */
function tax_rate_edit_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $tax_rate = $form_state['tax_rate'];
  $form_state['redirect'] = array('business-preferences/tax-rates/' . $tax_rate->tid . '/delete', array('query' => $destination));
}

/**
 * Form constructor for the tax rate deletion confirmation form.
 *
 * @see tax_rate_delete_confirm_form_submit()
 */
function tax_rate_delete_confirm_form($form, &$form_state, TaxRate $tax_rate) {
  $form_state['tax_rate'] = $tax_rate;
  return confirm_form($form,
    t('Are you sure you want to delete the tax rate?'),
    'business-preferences/tax-rates',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for tax_rate_delete_confirm_form().
 *
 * Deletes the tax rate.
 *
 * @see tax_rate_delete_confirm_form()
 */
function tax_rate_delete_confirm_form_submit($form, &$form_state) {
  $tax_rate = $form_state['tax_rate'];
  tax_rate_delete($tax_rate);
  drupal_set_message(t('The tax rate has been deleted.'));
  $form_state['redirect'] = '<front>';
}
