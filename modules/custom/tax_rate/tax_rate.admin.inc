<?php

/**
 * @file
 * Administration UI for the Tax rate module.
 */

/**
 * Generates the tax rate type editing form.
 */
function tax_rate_type_form($form, &$form_state, $tax_rate_type, $op = 'edit') {
  // Append 'clone' to the name when the entity is being cloned.
  if ($op == 'clone') {
    $tax_rate_type->name .= ' (cloned)';
    $tax_rate_type->type = '';
  }

  // Human readable name.
  $form['name'] = array(
    '#title' => t('Type name'),
    '#type' => 'textfield',
    '#default_value' => isset($tax_rate_type->name) ? $tax_rate_type->name : '',
    '#description' => t('The human-readable name of this tax rate type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine readable name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($tax_rate_type->type) ? $tax_rate_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'tax_rate_load',
      'source' => array('name'),
    ),
    '#description' => t('A unique machine-readable name for this tax rate type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save tax rate type'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete tax rate type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('tax_rate_type_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function tax_rate_type_form_submit(&$form, &$form_state) {
  $tax_rate_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $tax_rate_type->save();
  $form_state['redirect'] = 'admin/structure/tax_rates';
}

/**
 * Form API submit callback for the delete button.
 */
function tax_rate_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/tax_rates/manage/' . $form_state['tax_rate_type']->type . '/delete';
}
