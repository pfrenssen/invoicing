<?php
/**
 * @file
 * line_item.views.inc
 */

/**
 * Implements hook_views_data().
 */
function line_item_views_data() {
  $data = array();

  $data['tax_rates']['table']['group'] = t('Tax rates');

  $data['tax_rates']['table']['base'] = array(
    'title' => t('Tax rates'),
    'help' => t('Contains tax rate records we want to be exposed to Views.'),
  );

  // The ID field.
  $data['tax_rates']['tid'] = array(
    'title' => t('Tax rate ID'),
    'help' => t('The tax rate ID.'),
    'relationship' => array(
      'title' => t('Business'),
      'help' => t('Relate content to the business for which the user created it.'),
      'handler' => 'views_handler_relationship',
      'base' => 'business',
      'field' => 'bid',
      'label' => t('business'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // The Name field.
  $data['tax_rates']['name'] = array(
    'title' => t('Name'),
    'help' => t('The tax rate name.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // The rate field.
  $data['tax_rates']['rate'] = array(
    'title' => t('Rate'),
    'help' => t('The tax rate rate.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_field_numeric',
    ),
  );

  // The BID field.
  $data['tax_rates']['bid'] = array(
    'title' => t('Business ID'),
    'help' => t('The tax rate business ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  $data['tax_rates']['edit_tax_rate'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a link to the tax rate edit form.'),
      'handler' => 'tax_rate_handler_edit_link_field',
    ),
  );

  $data['tax_rates']['delete_tax_rate'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a link to delete the tax rate.'),
      'handler' => 'tax_rate_handler_delete_link_field',
    ),
  );

  return $data;
}
