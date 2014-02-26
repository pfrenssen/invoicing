<?php
/**
 * @file
 * business.features.inc
 */

/**
 * Implements hook_default_business_type().
 */
function business_default_business_type() {
  $items = array();
  $items['business'] = entity_import('business_type', '{ "type" : "business", "name" : "Business" }');
  return $items;
}

/**
 * Implements hook_views_api().
 */
function business_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
