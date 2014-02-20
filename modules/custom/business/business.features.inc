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
