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
