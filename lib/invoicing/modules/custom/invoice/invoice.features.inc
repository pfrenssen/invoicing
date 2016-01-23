<?php
/**
 * @file
 * invoice.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function invoice_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function invoice_views_api($module = NULL, $api = NULL) {
  return array(
    'api' => '3.0',
    'path' => drupal_get_path('module', 'invoice') . '/views',
  );
}

/**
 * Implements hook_default_invoice_type().
 */
function invoice_default_invoice_type() {
  $items = array();
  $items['invoice'] = entity_import('invoice_type', '{ "type" : "invoice", "name" : "Invoice" }');
  return $items;
}
