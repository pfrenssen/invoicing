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
      'title' => t('Total including VAT'),
      'help' => t('Provide the total price including VAT.'),
      'handler' => 'invoice_handler_total_field',
    ),
  );

  $data['invoice']['total_excl'] = array(
    'field' => array(
      'title' => t('Total excluding VAT'),
      'help' => t('Provide the total price excluding VAT.'),
      'handler' => 'invoice_handler_total_excl_field',
    ),
  );
}
