<?php

/**
 * @file
 * Drush integration for the Business module.
 */

/**
 * Implements hook_drush_command().
 */
function business_drush_command() {
  return array(
    'business-create' => array(
      'description' => 'Create a new business and link it to a user.',
      'arguments' => array(
        'business' => 'Name of the business to create.',
        'user' => 'Name of the user the business will be linked to.',
      ),
      'drupal dependencies' => array('business'),
      'examples' => array(
        'drush business-create \'My Company\' \'business owner\'' => 'Creates a company names \'My Company\' and links it to the user \'business owner\'.',
      ),
      'required-arguments' => TRUE,
      'category' => 'invoicing',
    ),
  );
}

/**
 * Drush command. Creates a business.
 */
function drush_business_create($business_name, $user_name) {
  if ($user = user_load_by_name($user_name)) {
    $business = business_create(array('name' => $business_name));
    $business->save();
    business_add_to_user($business, $user);
    drush_print('Business added to user.');
  }
  else {
    drush_set_error('User not found.');
  }
}
