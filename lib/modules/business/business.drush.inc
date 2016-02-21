<?php

/**
 * @file
 * Drush integration for the Business module.
 */

/**
 * Implements hook_drush_command().
 */
function business_drush_command() {
  return [
    'business-create' => [
      'description' => 'Create a new business and link it to a user.',
      'arguments' => [
        'business' => 'Name of the business to create.',
        'user' => 'Name of the user the business will be linked to.',
      ],
      'options' => [
        'email' => [
          'description' => 'Email address',
          'example-value' => 'business@example.com',
        ],
        'country' => [
          'description' => 'Country code',
          'example-value' => 'BE',
        ],
        'thoroughfare' => [
          'description' => 'Thoroughfare',
          'example-value' => 'Grote Markt 7',
        ],
        'postal-code' => [
          'description' => 'Postal code',
          'example-value' => '1000',
        ],
        'locality' => [
          'description' => 'Locality',
          'example-value' => 'Brussel',
        ],
        'vat' => [
          'description' => 'VAT number',
          'example-value' => 'BE0123456789',
        ],
        'phone' => [
          'description' => 'Phone number',
          'example-value' => '+3223456789',
        ],
        'mobile' => [
          'description' => 'Mobile phone number',
          'example-value' => '+32475286372',
        ],
        'bic' => [
          'description' => 'BIC number',
          'example-value' => 'BBBBEBB',
        ],
        'iban' => [
          'description' => 'IBAN number',
          'example-value' => 'BE68273690082883',
        ],
      ],
      'drupal dependencies' => ['business'],
      'examples' => [
        'drush business-create \'My Company\' \'business owner\'' => 'Creates a company names \'My Company\' and links it to the user \'business owner\'.',
      ],
      'required-arguments' => TRUE,
      'category' => 'invoicing',
    ],
  ];
}

/**
 * Drush command. Creates a business.
 */
function drush_business_create($business_name, $user_name) {
  if ($user = user_load_by_name($user_name)) {
    $values = [
      'name' => $business_name,
      'field_business_email' => drush_get_option('email'),
      'field_business_address' => [
        'country' => drush_get_option('country'),
        'thoroughfare' => drush_get_option('thoroughfare'),
        'postal_code' => drush_get_option('postal-code'),
        'locality' => drush_get_option('locality'),
      ],
      'field_business_vat' => drush_get_option('vat'),
      'field_business_phone' => [
        'number' => drush_get_option('phone'),
        'countrycode' => drush_get_option('country'),
      ],
      'field_business_mobile' => [
        'number' => drush_get_option('mobile'),
        'countrycode' => drush_get_option('country'),
      ],
      'field_business_bic' => drush_get_option('bic'),
      'field_business_iban' => drush_get_option('iban'),
    ];
    $business = business_create();
    $wrapper = entity_metadata_wrapper('business', $business);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
    $business->save();
    business_add_to_user($business, $user);
    drush_print('Business added to user.');
  }
  else {
    drush_set_error('User not found.');
  }
}
