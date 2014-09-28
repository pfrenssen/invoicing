<?php
/**
 * @file
 * tax_rate.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function tax_rate_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'tax_rate-tax_rate-field_tax_rate_name'
  $field_instances['tax_rate-tax_rate-field_tax_rate_name'] = array(
    'bundle' => 'tax_rate',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'tax_rate',
    'field_name' => 'field_tax_rate_name',
    'label' => 'Name',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'tax_rate-tax_rate-field_tax_rate_rate'
  $field_instances['tax_rate-tax_rate-field_tax_rate_rate'] = array(
    'bundle' => 'tax_rate',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'tax_rate',
    'field_name' => 'field_tax_rate_rate',
    'label' => 'Rate',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Name');
  t('Rate');

  return $field_instances;
}
