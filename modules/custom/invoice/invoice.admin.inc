<?php

/**
 * @file
 * Administration UI for the Invoice module.
 */

/**
 * Generates the invoice type editing form.
 */
function invoice_type_form($form, &$form_state, $invoice_type, $op = 'edit') {
  // Append 'clone' to the name when the entity is being cloned.
  if ($op == 'clone') {
    $invoice_type->name .= ' (cloned)';
    $invoice_type->type = '';
  }

  // Human readable name.
  $form['name'] = array(
    '#title' => t('Type name'),
    '#type' => 'textfield',
    '#default_value' => isset($invoice_type->name) ? $invoice_type->name : '',
    '#description' => t('The human-readable name of this invoice type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine readable name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($invoice_type->type) ? $invoice_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'invoice_load',
      'source' => array('name'),
    ),
    '#description' => t('A unique machine-readable name for this invoice type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save invoice type'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete invoice type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('invoice_type_form_submit_delete')
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function invoice_type_form_submit(&$form, &$form_state) {
  $invoice_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $invoice_type->save();
  $form_state['redirect'] = 'admin/structure/invoices';
}

/**
 * Form API submit callback for the delete button.
 */
function invoice_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/invoices/manage/' . $form_state['invoice_type']->type . '/delete';
}
