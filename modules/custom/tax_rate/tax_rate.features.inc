<?php
/**
 * @file
 * tax_rate.features.inc
 */

/**
 * Implements hook_views_api().
 */
function tax_rate_views_api($module = NULL, $api = NULL) {
  return array(
    'api' => '3.0',
    'path' => drupal_get_path('module', 'tax_rate') . '/views',
  );
}

/**
 * Implements hook_default_tax_rate_type().
 */
function tax_rate_default_tax_rate_type() {
  $items = array();
  $items['tax_rate'] = entity_import('tax_rate_type', '{ "type" : "tax_rate", "name" : "Tax rate" }');
  return $items;
}
