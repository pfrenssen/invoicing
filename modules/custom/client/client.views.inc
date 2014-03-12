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
  $data['entity']['edit_link'] = array(
    'group' => t('Client'),
    'real field' => 'cid',
    'title' => t('Edit client link'),
    'help' => t('Link to the client edit screen.'),
    'field' => array(
      'handler' => 'client_handler_field_entity_link_edit',
    ),
  );

  return $data;
}
