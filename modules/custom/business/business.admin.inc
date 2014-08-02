<?php

/**
 * @file
 * Administration UI for the Business module.
 */

/**
 * Generates the business type editing form.
 */
function business_type_form($form, &$form_state, $business_type, $op = 'edit') {
  // Append 'clone' to the name when the entity is being cloned.
  if ($op == 'clone') {
    $business_type->name .= ' (cloned)';
    $business_type->type = '';
  }

  // Human readable name.
  $form['name'] = array(
    '#title' => t('Type name'),
    '#type' => 'textfield',
    '#default_value' => isset($business_type->name) ? $business_type->name : '',
    '#description' => t('The human-readable name of this business type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine readable name.
  $form['business'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($business_type->type) ? $business_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'business_load',
      'source' => array('name'),
    ),
    '#description' => t('A unique machine-readable name for this business type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save business type'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete business type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('business_type_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function business_type_form_submit(&$form, &$form_state) {
  $business_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $business_type->save();
  $form_state['redirect'] = 'admin/structure/businesses';
}

/**
 * Form API submit callback for the delete button.
 */
function business_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/businesses/manage/' . $form_state['business_type']->type . '/delete';
}
