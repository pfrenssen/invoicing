<?php

/**
 * @file
 * Administration UI for the Client module.
 */

/**
 * Generates the client type editing form.
 */
function client_type_form($form, &$form_state, $client_type, $op = 'edit') {
  // Append 'clone' to the name when the entity is being cloned.
  if ($op == 'clone') {
    $client_type->name .= ' (cloned)';
    $client_type->type = '';
  }

  // Human readable name.
  $form['name'] = array(
    '#title' => t('Type name'),
    '#type' => 'textfield',
    '#default_value' => isset($client_type->name) ? $client_type->name : '',
    '#description' => t('The human-readable name of this client type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine readable name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($client_type->type) ? $client_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'client_load',
      'source' => array('name'),
    ),
    '#description' => t('A unique machine-readable name for this client type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save client type'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete client type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('client_type_form_submit_delete')
    );
  }

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function client_type_form_submit(&$form, &$form_state) {
  $client_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $client_type->save();
  $form_state['redirect'] = 'admin/structure/clients';
}

/**
 * Form API submit callback for the delete button.
 */
function client_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/clients/manage/' . $form_state['client_type']->type . '/delete';
}
