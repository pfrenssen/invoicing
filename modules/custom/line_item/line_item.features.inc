<?php
/**
 * @file
 * line_item.features.inc
 */

/**
 * Implements hook_views_api().
 */
function line_item_views_api($module = NULL, $api = NULL) {
  return array(
    'api' => '3.0',
    'path' => drupal_get_path('module', 'line_item') . '/views',
  );
}

/**
 * Implements hook_default_line_item_type().
 */
function line_item_default_line_item_type() {
  $items = array();
  $items['product'] = entity_import('line_item_type', '{ "type" : "product", "name" : "Product" }');
  $items['service'] = entity_import('line_item_type', '{ "type" : "service", "name" : "Service" }');
  return $items;
}
