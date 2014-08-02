<?php
/**
 * @file
 * client.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function client_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'clients';
  $view->description = 'Client overview';
  $view->tag = 'default';
  $view->base_table = 'client';
  $view->human_name = 'Clients';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Clients';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access client overview';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'cid' => 'cid',
    'name' => 'name',
    'field_client_email' => 'field_client_email',
    'field_client_phone' => 'field_client_phone',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'cid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_client_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_client_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Client: Client ID */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'client';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  /* Field: Client: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'client';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Client';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'client/[cid]';
  /* Field: Client: Email address */
  $handler->display->display_options['fields']['field_client_email']['id'] = 'field_client_email';
  $handler->display->display_options['fields']['field_client_email']['table'] = 'field_data_field_client_email';
  $handler->display->display_options['fields']['field_client_email']['field'] = 'field_client_email';
  /* Field: Client: Phone number */
  $handler->display->display_options['fields']['field_client_phone']['id'] = 'field_client_phone';
  $handler->display->display_options['fields']['field_client_phone']['table'] = 'field_data_field_client_phone';
  $handler->display->display_options['fields']['field_client_phone']['field'] = 'field_client_phone';
  /* Field: Client: Website */
  $handler->display->display_options['fields']['field_client_website']['id'] = 'field_client_website';
  $handler->display->display_options['fields']['field_client_website']['table'] = 'field_data_field_client_website';
  $handler->display->display_options['fields']['field_client_website']['field'] = 'field_client_website';
  $handler->display->display_options['fields']['field_client_website']['click_sort_column'] = 'url';
  /* Field: Client: Edit link */
  $handler->display->display_options['fields']['edit_client']['id'] = 'edit_client';
  $handler->display->display_options['fields']['edit_client']['table'] = 'client';
  $handler->display->display_options['fields']['edit_client']['field'] = 'edit_client';
  $handler->display->display_options['fields']['edit_client']['label'] = 'Actions';
  /* Contextual filter: Client: Business */
  $handler->display->display_options['arguments']['bid']['id'] = 'bid';
  $handler->display->display_options['arguments']['bid']['table'] = 'client';
  $handler->display->display_options['arguments']['bid']['field'] = 'bid';
  $handler->display->display_options['arguments']['bid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['bid']['default_argument_type'] = 'business_active';
  $handler->display->display_options['arguments']['bid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['bid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['bid']['summary_options']['items_per_page'] = '25';

  /* Display: Overview */
  $handler = $view->new_display('page', 'Overview', 'overview');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access client overview';
  $handler->display->display_options['path'] = 'clients';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Clients';
  /* Display: Admin overview */
  $handler = $view->new_display('page', 'Admin overview', 'admin_overview');
  $handler->display->display_options['display_comment'] = 'This is altered by invoicing_core_views_pre_view() to be also visible on the /clients path for administrators.';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer businesses';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Client: Business */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'client';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Business: Business ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'business';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  $handler->display->display_options['fields']['bid']['relationship'] = 'bid';
  $handler->display->display_options['fields']['bid']['exclude'] = TRUE;
  /* Field: Business: Label */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'business';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'bid';
  $handler->display->display_options['fields']['name_1']['label'] = 'Business';
  $handler->display->display_options['fields']['name_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name_1']['alter']['path'] = 'business/[bid]';
  /* Field: Client: Client ID */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'client';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['exclude'] = TRUE;
  /* Field: Client: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'client';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Client';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'client/[cid]';
  /* Field: Client: Email address */
  $handler->display->display_options['fields']['field_client_email']['id'] = 'field_client_email';
  $handler->display->display_options['fields']['field_client_email']['table'] = 'field_data_field_client_email';
  $handler->display->display_options['fields']['field_client_email']['field'] = 'field_client_email';
  /* Field: Client: Phone number */
  $handler->display->display_options['fields']['field_client_phone']['id'] = 'field_client_phone';
  $handler->display->display_options['fields']['field_client_phone']['table'] = 'field_data_field_client_phone';
  $handler->display->display_options['fields']['field_client_phone']['field'] = 'field_client_phone';
  /* Field: Client: Website */
  $handler->display->display_options['fields']['field_client_website']['id'] = 'field_client_website';
  $handler->display->display_options['fields']['field_client_website']['table'] = 'field_data_field_client_website';
  $handler->display->display_options['fields']['field_client_website']['field'] = 'field_client_website';
  $handler->display->display_options['fields']['field_client_website']['click_sort_column'] = 'url';
  /* Field: Client: Edit link */
  $handler->display->display_options['fields']['edit_client']['id'] = 'edit_client';
  $handler->display->display_options['fields']['edit_client']['table'] = 'client';
  $handler->display->display_options['fields']['edit_client']['field'] = 'edit_client';
  $handler->display->display_options['fields']['edit_client']['label'] = 'Actions';
  $handler->display->display_options['path'] = 'admin/clients';
  $export['clients'] = $view;

  return $export;
}
