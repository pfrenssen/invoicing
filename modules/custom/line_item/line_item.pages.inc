<?php

/**
 * @file
 * Page callbacks for adding, editing and deleting line items.
 */

/**
 * Page callback: Choose for which line item type to create a new line item for.
 */
function line_item_type_add_page() {
  $types = line_item_get_types();

  $items = array();
  foreach ($types as $type) {
    $items[] = l($type->name, 'line_item/add/' . $type->type);
  }

  return theme('item_list', array('items' => $items, 'title' => NULL));
}

/**
 * Page callback: Returns the line item add/edit form to add a new line item.
 *
 * @see line_item_edit_form()
 *
 * @param object $line_item_type
 *   The type of line_item to create.
 *
 * @return array
 *   The line item add/edit form render array.
 */
function line_item_add_page($line_item_type) {
  $line_item = entity_create('line_item', array('type' => $line_item_type->type));

  return drupal_get_form('line_item_edit_form', $line_item);
}

/**
 * Page callback: Returns the line item add/edit form to edit an existing line
 * item.
 *
 * @see line_item_edit_form()
 *
 * @param LineItem $line_item
 *   The line item to edit.
 *
 * @return array
 *   The line item add/edit form render array.
 */
function line_item_edit_page(LineItem $line_item) {
  drupal_set_title(t('Edit line item'));

  return drupal_get_form('line_item_edit_form', $line_item);
}

/**
 * Form constructor for the line item add/edit form.
 *
 * @param LineItem $line_item
 *   The line item that is being added/edited.
 *
 * @ingroup forms
 */
function line_item_edit_form($form, &$form_state, LineItem $line_item) {
  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['line_item'])) {
    $form_state['line_item'] = $line_item;
  }
  else {
    $line_item = $form_state['line_item'];
  }

  // Attach all form elements for the fields.
  field_attach_form('line_item', $line_item, $form, $form_state, entity_language('line_item', $line_item));

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('line_item_edit_form_submit'),
  );

  if (!empty($line_item->lid) && line_item_access('delete', $line_item)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('line_item_edit_form_delete_submit'),
    );
  }

  return $form;
}

/**
 * Form validation handler for line_item_edit_form().
 */
function line_item_edit_form_validate($form, &$form_state) {
  field_attach_form_validate('line_item', $form_state['line_item'], $form, $form_state);
}

/**
 * Form submission handler for line_item_edit_form().
 *
 * Saves a line item and outputs a status message to the user.
 */
function line_item_edit_form_submit($form, &$form_state) {
  $line_item = $form_state['line_item'];
  entity_form_submit_build_entity('line_item', $line_item, $form, $form_state);

  $operation = !empty($line_item->is_new) ? 'add' : 'edit';

  if (line_item_save($line_item)) {
    $message = $operation == 'add' ? 'New line item has been added.' : 'The changes have been saved.';
    drupal_set_message(t($message));
  }
  else {
    drupal_set_message(t('The line item could not be saved.'), 'error');
    watchdog('line_item', 'Line item could not be saved.', WATCHDOG_ERROR);
  }

  $form_state['redirect'] = 'line_items';
}

/**
 * Form submission handler for line_item_edit_form().
 *
 * Handles the 'Delete' button on the node form.
 *
 * @see line_item_edit_form()
 * @see line_item_delete_confirm_form()
 */
function line_item_edit_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $line_item = $form_state['line_item'];
  $form_state['redirect'] = array('line_item/' . $line_item->lid . '/delete', array('query' => $destination));
}

/**
 * Form constructor for the line item deletion confirmation form.
 *
 * @see line_item_delete_confirm_form_submit()
 */
function line_item_delete_confirm_form($form, &$form_state, LineItem $line_item) {
  $form_state['line_item'] = $line_item;
  return confirm_form($form,
    t('Are you sure you want to delete the line item?'),
    'line_item/' . $line_item->lid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for line_item_delete_confirm_form().
 *
 * Deletes the line item.
 *
 * @see line item_delete_confirm_form()
 */
function line_item_delete_confirm_form_submit($form, &$form_state) {
  $line_item = $form_state['line_item'];
  line_item_delete($line_item);
  drupal_set_message(t('The line item has been deleted.'));
  $form_state['redirect'] = 'line_items';
}

/**
 * Page callback for the line item page.
 */
function line_item_detail_page($line_item) {
  $output = entity_view('line_item', array($line_item));

  // Prevent the line item title from being rendered twice.
  $output['line_item'][$line_item->lid]['#page'] = TRUE;

  return $output;
}
