<?php

/**
 * @file
 * This file handles views api definitions.
 * We describe the table to Views module
 * as well as other necessary stuff to integrate
 */

/**
 * Implements hook_views_data_alter().
 */
function tax_rate_views_data_alter(&$data) {
  $data['tax_rate']['link_tax_rate'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the tax rate.'),
      'handler' => 'tax_rate_handler_link_field',
    ),
  );
  $data['tax_rate']['edit_tax_rate'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a link to the tax rate edit form.'),
      'handler' => 'tax_rate_handler_edit_link_field',
    ),
  );
  $data['tax_rate']['delete_tax_rate'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a link to delete the tax rate.'),
      'handler' => 'tax_rate_handler_delete_link_field',
    ),
  );
}
