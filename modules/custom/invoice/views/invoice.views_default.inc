<?php
/**
 * @file
 * Exported views for the Invoice module.
 */

/**
 * Implements hook_views_default_views().
 */
function invoice_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'invoices';
  $view->description = 'Invoice overview';
  $view->tag = 'default';
  $view->base_table = 'invoice';
  $view->human_name = 'Invoices';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Invoices';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access invoice overview';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'iid' => 'iid',
    'field_invoice_number' => 'field_invoice_number',
    'field_invoice_client' => 'field_invoice_client',
    'field_invoice_date' => 'field_invoice_date',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'iid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_invoice_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_invoice_client' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_invoice_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No invoices yet! Why don\'t you go ahead and create one?';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Field: Invoice: Invoice ID */
  $handler->display->display_options['fields']['iid']['id'] = 'iid';
  $handler->display->display_options['fields']['iid']['table'] = 'invoice';
  $handler->display->display_options['fields']['iid']['field'] = 'iid';
  $handler->display->display_options['fields']['iid']['exclude'] = TRUE;
  /* Field: Invoice: Invoice number */
  $handler->display->display_options['fields']['field_invoice_number']['id'] = 'field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['table'] = 'field_data_field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['field'] = 'field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_invoice_number']['alter']['path'] = 'invoice/[iid]';
  /* Field: Invoice: Client */
  $handler->display->display_options['fields']['field_invoice_client']['id'] = 'field_invoice_client';
  $handler->display->display_options['fields']['field_invoice_client']['table'] = 'field_data_field_invoice_client';
  $handler->display->display_options['fields']['field_invoice_client']['field'] = 'field_invoice_client';
  $handler->display->display_options['fields']['field_invoice_client']['settings'] = array(
    'link' => 1,
  );
  /* Field: Invoice: Date */
  $handler->display->display_options['fields']['field_invoice_date']['id'] = 'field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['table'] = 'field_data_field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['field'] = 'field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Invoice: Total excluding VAT */
  $handler->display->display_options['fields']['total_ex_vat']['id'] = 'total_ex_vat';
  $handler->display->display_options['fields']['total_ex_vat']['table'] = 'invoice';
  $handler->display->display_options['fields']['total_ex_vat']['field'] = 'total_ex_vat';
  $handler->display->display_options['fields']['total_ex_vat']['precision'] = '0';
  /* Field: Invoice: Total including VAT */
  $handler->display->display_options['fields']['total_inc_vat']['id'] = 'total_inc_vat';
  $handler->display->display_options['fields']['total_inc_vat']['table'] = 'invoice';
  $handler->display->display_options['fields']['total_inc_vat']['field'] = 'total_inc_vat';
  $handler->display->display_options['fields']['total_inc_vat']['precision'] = '0';
  /* Contextual filter: Invoice: Business */
  $handler->display->display_options['arguments']['bid']['id'] = 'bid';
  $handler->display->display_options['arguments']['bid']['table'] = 'invoice';
  $handler->display->display_options['arguments']['bid']['field'] = 'bid';
  $handler->display->display_options['arguments']['bid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['bid']['default_argument_type'] = 'business_active';
  $handler->display->display_options['arguments']['bid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['bid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['bid']['summary_options']['items_per_page'] = '25';

  /* Display: Overview */
  $handler = $view->new_display('page', 'Overview', 'overview');
  $handler->display->display_options['display_comment'] = 'This display is altered in invoicing_core_views_pre_view(). That filters all views that use the "active business" contextual arguments to ensure the filter cannot be bypassed by appending "/all" to the URL. Otherwise this would expose invoices of other users.';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access invoice overview';
  $handler->display->display_options['path'] = 'invoices';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Invoices';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Admin overview */
  $handler = $view->new_display('page', 'Admin overview', 'admin_overview');
  $handler->display->display_options['display_comment'] = 'This is altered by invoicing_core_views_pre_view() to be also visible on the /invoices path for administrators.';
  $handler->display->display_options['display_description'] = 'Shows invoices of all businesses for administrators';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer businesses';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Invoice: Business */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'invoice';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Business: Business ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'business';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  $handler->display->display_options['fields']['bid']['relationship'] = 'bid';
  $handler->display->display_options['fields']['bid']['exclude'] = TRUE;
  /* Field: Business: Label */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'business';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'bid';
  $handler->display->display_options['fields']['name']['label'] = 'Business';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'business/[bid]';
  /* Field: Invoice: Invoice ID */
  $handler->display->display_options['fields']['iid']['id'] = 'iid';
  $handler->display->display_options['fields']['iid']['table'] = 'invoice';
  $handler->display->display_options['fields']['iid']['field'] = 'iid';
  $handler->display->display_options['fields']['iid']['exclude'] = TRUE;
  /* Field: Invoice: Invoice number */
  $handler->display->display_options['fields']['field_invoice_number']['id'] = 'field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['table'] = 'field_data_field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['field'] = 'field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_invoice_number']['alter']['path'] = 'invoice/[iid]';
  /* Field: Invoice: Client */
  $handler->display->display_options['fields']['field_invoice_client']['id'] = 'field_invoice_client';
  $handler->display->display_options['fields']['field_invoice_client']['table'] = 'field_data_field_invoice_client';
  $handler->display->display_options['fields']['field_invoice_client']['field'] = 'field_invoice_client';
  $handler->display->display_options['fields']['field_invoice_client']['settings'] = array(
    'link' => 1,
  );
  /* Field: Invoice: Date */
  $handler->display->display_options['fields']['field_invoice_date']['id'] = 'field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['table'] = 'field_data_field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['field'] = 'field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Invoice: Total excluding VAT */
  $handler->display->display_options['fields']['total_ex_vat']['id'] = 'total_ex_vat';
  $handler->display->display_options['fields']['total_ex_vat']['table'] = 'invoice';
  $handler->display->display_options['fields']['total_ex_vat']['field'] = 'total_ex_vat';
  $handler->display->display_options['fields']['total_ex_vat']['precision'] = '0';
  /* Field: Invoice: Total including VAT */
  $handler->display->display_options['fields']['total_inc_vat']['id'] = 'total_inc_vat';
  $handler->display->display_options['fields']['total_inc_vat']['table'] = 'invoice';
  $handler->display->display_options['fields']['total_inc_vat']['field'] = 'total_inc_vat';
  $handler->display->display_options['fields']['total_inc_vat']['precision'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Business: Label */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'business';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'bid';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Business';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['path'] = 'admin/invoices';

  /* Display: Client invoices */
  $handler = $view->new_display('panel_pane', 'Client invoices', 'client');
  $handler->display->display_options['display_description'] = 'Pane listing the invoices for the given client.';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Invoice: Invoice ID */
  $handler->display->display_options['fields']['iid']['id'] = 'iid';
  $handler->display->display_options['fields']['iid']['table'] = 'invoice';
  $handler->display->display_options['fields']['iid']['field'] = 'iid';
  $handler->display->display_options['fields']['iid']['exclude'] = TRUE;
  /* Field: Invoice: Invoice number */
  $handler->display->display_options['fields']['field_invoice_number']['id'] = 'field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['table'] = 'field_data_field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['field'] = 'field_invoice_number';
  $handler->display->display_options['fields']['field_invoice_number']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_invoice_number']['alter']['path'] = 'invoice/[iid]';
  /* Field: Invoice: Date */
  $handler->display->display_options['fields']['field_invoice_date']['id'] = 'field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['table'] = 'field_data_field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['field'] = 'field_invoice_date';
  $handler->display->display_options['fields']['field_invoice_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Invoice: Total excluding VAT */
  $handler->display->display_options['fields']['total_ex_vat']['id'] = 'total_ex_vat';
  $handler->display->display_options['fields']['total_ex_vat']['table'] = 'invoice';
  $handler->display->display_options['fields']['total_ex_vat']['field'] = 'total_ex_vat';
  $handler->display->display_options['fields']['total_ex_vat']['precision'] = '0';
  /* Field: Invoice: Total including VAT */
  $handler->display->display_options['fields']['total_inc_vat']['id'] = 'total_inc_vat';
  $handler->display->display_options['fields']['total_inc_vat']['table'] = 'invoice';
  $handler->display->display_options['fields']['total_inc_vat']['field'] = 'total_inc_vat';
  $handler->display->display_options['fields']['total_inc_vat']['precision'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Invoice: Client (field_invoice_client:target_id) */
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['id'] = 'field_invoice_client_target_id';
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['table'] = 'field_data_field_invoice_client';
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['field'] = 'field_invoice_client_target_id';
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_invoice_client_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['pane_title'] = 'Client invoices';
  $handler->display->display_options['pane_description'] = 'Pane listing the invoices for the given client.';
  $handler->display->display_options['argument_input'] = array(
    'field_invoice_client_target_id' => array(
      'type' => 'context',
      'context' => 'entity:client.cid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Invoice: Client (field_invoice_client:target_id)',
    ),
  );
  $export['invoices'] = $view;

  return $export;
}
