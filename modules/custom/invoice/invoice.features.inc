<?php
/**
 * @file
 * invoice.features.inc
 */

/**
 * Implements hook_default_invoice_type().
 */
function invoice_default_invoice_type() {
  $items = array();
  $items['invoice'] = entity_import('invoice_type', '{ "type" : "invoice", "name" : "Invoice" }');
  return $items;
}
