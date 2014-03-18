<?php
/**
 * @file
 * invoice.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function invoice_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'invoice-invoice-field_invoice_client'
  $field_instances['invoice-invoice-field_invoice_client'] = array(
    'bundle' => 'invoice',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'invoice',
    'field_name' => 'field_invoice_client',
    'label' => 'Client id',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Client id');

  return $field_instances;
}
