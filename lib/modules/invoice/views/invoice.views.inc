<?php

/**
 * @file
 * Views integration for the Invoice module.
 */

/**
 * Implements hook_views_data_alter().
 */
function invoice_views_data_alter(&$data) {
  $data['invoice']['total'] = array(
    'field' => array(
      'title' => t('Total'),
      'help' => t('The total price including VAT.'),
      'handler' => 'invoice_handler_total_field',
      'float' => TRUE,
    ),
  );

  $data['invoice']['total_excl'] = array(
    'field' => array(
      'title' => t('Total ex VAT'),
      'help' => t('The total price excluding VAT.'),
      'handler' => 'invoice_handler_total_excl_field',
      'float' => TRUE,
    ),
  );
}
