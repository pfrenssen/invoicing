<?php
/**
 * @file
 * client.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function client_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'client-client-field_client_address'
  $field_instances['client-client-field_client_address'] = array(
    'bundle' => 'client',
    'default_value' => array(
      0 => array(
        'element_key' => 'client|client|field_client_address|und|0',
        'thoroughfare' => '',
        'premise' => '',
        'postal_code' => '',
        'locality' => '',
        'country' => 'BE',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'client',
    'field_name' => 'field_client_address',
    'label' => 'Address',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(),
        'format_handlers' => array(
          'address' => 'address',
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'client-client-field_client_email'
  $field_instances['client-client-field_client_email'] = array(
    'bundle' => 'client',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'email',
        'settings' => array(),
        'type' => 'email_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'client',
    'field_name' => 'field_client_email',
    'label' => 'Email address',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Email address');

  return $field_instances;
}
