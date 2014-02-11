<?php
/**
 * @file
 * client.features.inc
 */

/**
 * Implements hook_default_client_type().
 */
function client_default_client_type() {
  $items = array();
  $items['client'] = entity_import('client_type', '{ "type" : "client", "name" : "Client" }');
  return $items;
}

/**
 * Implements hook_views_api().
 */
function client_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
