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
function client_views_data() {
  $data = array();

  $data['client']['edit_link'] = array(
    'group' => t('Client'),
    'real field' => 'cid',
    'title' => t('Edit link'),
    'help' => t('The edit link of the client'),
    'field' => array(
      'handler' => 'client_handler_field_client_edit_link',
    ),
  );

  return $data;
}
