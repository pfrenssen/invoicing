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
function client_views_data_alter(&$data) {
  $data['client']['link_client'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the client.'),
      'handler' => 'client_handler_link_field',
    ),
  );
  $data['client']['edit_client'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a link to the client edit form.'),
      'handler' => 'client_handler_edit_link_field',
    ),
  );
  $data['client']['delete_client'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a link to delete the client.'),
      'handler' => 'client_handler_delete_link_field',
    ),
  );
}
