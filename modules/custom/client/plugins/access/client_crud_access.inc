<?php

/**
 * @file
 * CTools access plugin for CRUD operations on Client entities.
 */

$plugin = array(
  'title' => t('Client: CRUD access'),
  'description' => t('Determine access to CRUD operations on Client entities.'),
  'callback' => 'client_crud_access_ctools_access_check',
  'settings form' => 'client_crud_access_ctools_access_settings',
  'summary' => 'client_crud_access_ctools_access_summary',
  // @todo This should not be required when creating a new client.
  'required context' => new ctools_context_required(t('Client'), 'client'),
);

/**
 * Settings form for the access plugin.
 *
 * @todo Add support for other users than the current user.
 */
function client_crud_access_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['operation'] = array(
    '#type' => 'radios',
    '#title' => t('Operation'),
    '#options' => array(
      'view' => t('View'),
      'create' => t('Create'),
      'edit' => t('Edit'),
      'delete' => t('Delete'),
    ),
    '#default_value' => !empty($conf['operation']) ? $conf['operation'] : 'view',
  );

  return $form;
}

/**
 * Checks for access.
 */
function client_crud_access_ctools_access_check($conf, $context) {
  if (empty($context->data) || !is_object($context->data) || ! $context->data instanceof Client) {
    return FALSE;
  }
  return client_access($conf['operation'], $context->data);
}

/**
 * Provide a summary description based upon the checked roles.
 */
function client_crud_access_ctools_access_summary($conf, $context) {
  $args = array('@operation' => $conf['operation']);
  return t('The current user has permission to @operation a client.', $args);
}
