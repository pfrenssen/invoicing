<?php
/**
 * @file
 * business.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function business_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'businesses';
  $view->description = 'Business overview';
  $view->tag = 'default';
  $view->base_table = 'business';
  $view->human_name = 'Businesses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Businesses';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer businesses';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Business: Business ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'business';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  $handler->display->display_options['fields']['bid']['exclude'] = TRUE;
  /* Field: Business: Name */
  $handler->display->display_options['fields']['field_business_name']['id'] = 'field_business_name';
  $handler->display->display_options['fields']['field_business_name']['table'] = 'field_data_field_business_name';
  $handler->display->display_options['fields']['field_business_name']['field'] = 'field_business_name';
  $handler->display->display_options['fields']['field_business_name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_business_name']['alter']['path'] = 'business/[bid]';
  /* Field: Business: Email address */
  $handler->display->display_options['fields']['field_business_email']['id'] = 'field_business_email';
  $handler->display->display_options['fields']['field_business_email']['table'] = 'field_data_field_business_email';
  $handler->display->display_options['fields']['field_business_email']['field'] = 'field_business_email';
  /* Field: Business: Mobile number */
  $handler->display->display_options['fields']['field_business_mobile']['id'] = 'field_business_mobile';
  $handler->display->display_options['fields']['field_business_mobile']['table'] = 'field_data_field_business_mobile';
  $handler->display->display_options['fields']['field_business_mobile']['field'] = 'field_business_mobile';
  $handler->display->display_options['fields']['field_business_mobile']['exclude'] = TRUE;
  /* Field: Business: Phone number */
  $handler->display->display_options['fields']['field_business_phone']['id'] = 'field_business_phone';
  $handler->display->display_options['fields']['field_business_phone']['table'] = 'field_data_field_business_phone';
  $handler->display->display_options['fields']['field_business_phone']['field'] = 'field_business_phone';
  $handler->display->display_options['fields']['field_business_phone']['empty'] = '[field_business_mobile] ';
  $handler->display->display_options['fields']['field_business_phone']['hide_alter_empty'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/business/[bid]/edit">edit</a>';
  /* Sort criterion: Business: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'business';
  $handler->display->display_options['sorts']['name']['field'] = 'name';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_businesses');
  $handler->display->display_options['path'] = 'businesses';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Businesses';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['businesses'] = $view;

  return $export;
}
