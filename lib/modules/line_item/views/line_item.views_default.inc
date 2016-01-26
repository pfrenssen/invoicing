<?php
/**
 * @file
 * line_item.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function line_item_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'line_items';
  $view->description = 'Tables containing products and services';
  $view->tag = 'default';
  $view->base_table = 'line_item';
  $view->human_name = 'Line items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'lid' => 'lid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'lid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_invoice_products_invoice']['id'] = 'reverse_field_invoice_products_invoice';
  $handler->display->display_options['relationships']['reverse_field_invoice_products_invoice']['table'] = 'line_item';
  $handler->display->display_options['relationships']['reverse_field_invoice_products_invoice']['field'] = 'reverse_field_invoice_products_invoice';
  $handler->display->display_options['relationships']['reverse_field_invoice_products_invoice']['required'] = TRUE;
  /* Field: Line item: Description */
  $handler->display->display_options['fields']['field_line_item_description']['id'] = 'field_line_item_description';
  $handler->display->display_options['fields']['field_line_item_description']['table'] = 'field_data_field_line_item_description';
  $handler->display->display_options['fields']['field_line_item_description']['field'] = 'field_line_item_description';
  /* Field: Line item: Quantity */
  $handler->display->display_options['fields']['field_line_item_quantity']['id'] = 'field_line_item_quantity';
  $handler->display->display_options['fields']['field_line_item_quantity']['table'] = 'field_data_field_line_item_quantity';
  $handler->display->display_options['fields']['field_line_item_quantity']['field'] = 'field_line_item_quantity';
  $handler->display->display_options['fields']['field_line_item_quantity']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Unit cost */
  $handler->display->display_options['fields']['field_line_item_unit_cost']['id'] = 'field_line_item_unit_cost';
  $handler->display->display_options['fields']['field_line_item_unit_cost']['table'] = 'field_data_field_line_item_unit_cost';
  $handler->display->display_options['fields']['field_line_item_unit_cost']['field'] = 'field_line_item_unit_cost';
  $handler->display->display_options['fields']['field_line_item_unit_cost']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Tax */
  $handler->display->display_options['fields']['field_line_item_tax']['id'] = 'field_line_item_tax';
  $handler->display->display_options['fields']['field_line_item_tax']['table'] = 'field_data_field_line_item_tax';
  $handler->display->display_options['fields']['field_line_item_tax']['field'] = 'field_line_item_tax';
  $handler->display->display_options['fields']['field_line_item_tax']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Discount */
  $handler->display->display_options['fields']['field_line_item_discount']['id'] = 'field_line_item_discount';
  $handler->display->display_options['fields']['field_line_item_discount']['table'] = 'field_data_field_line_item_discount';
  $handler->display->display_options['fields']['field_line_item_discount']['field'] = 'field_line_item_discount';
  $handler->display->display_options['fields']['field_line_item_discount']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Total */
  $handler->display->display_options['fields']['field_line_item_total']['id'] = 'field_line_item_total';
  $handler->display->display_options['fields']['field_line_item_total']['table'] = 'line_item';
  $handler->display->display_options['fields']['field_line_item_total']['field'] = 'field_line_item_total';
  /* Contextual filter: Invoice: Invoice ID */
  $handler->display->display_options['arguments']['iid']['id'] = 'iid';
  $handler->display->display_options['arguments']['iid']['table'] = 'invoice';
  $handler->display->display_options['arguments']['iid']['field'] = 'iid';
  $handler->display->display_options['arguments']['iid']['relationship'] = 'reverse_field_invoice_services_invoice';
  $handler->display->display_options['arguments']['iid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['iid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['iid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['iid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['iid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Line item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'service' => 'service',
  );

  /* Display: Products */
  $handler = $view->new_display('panel_pane', 'Products', 'products');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Invoice: Invoice ID */
  $handler->display->display_options['arguments']['iid']['id'] = 'iid';
  $handler->display->display_options['arguments']['iid']['table'] = 'invoice';
  $handler->display->display_options['arguments']['iid']['field'] = 'iid';
  $handler->display->display_options['arguments']['iid']['relationship'] = 'reverse_field_invoice_products_invoice';
  $handler->display->display_options['arguments']['iid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['iid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['iid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['iid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['iid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Line item: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'line_item';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'product' => 'product',
  );

  /* Display: Services */
  $handler = $view->new_display('panel_pane', 'Services', 'services');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_invoice_services_invoice']['id'] = 'reverse_field_invoice_services_invoice';
  $handler->display->display_options['relationships']['reverse_field_invoice_services_invoice']['table'] = 'line_item';
  $handler->display->display_options['relationships']['reverse_field_invoice_services_invoice']['field'] = 'reverse_field_invoice_services_invoice';
  $handler->display->display_options['relationships']['reverse_field_invoice_services_invoice']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Line item: Description */
  $handler->display->display_options['fields']['field_line_item_description']['id'] = 'field_line_item_description';
  $handler->display->display_options['fields']['field_line_item_description']['table'] = 'field_data_field_line_item_description';
  $handler->display->display_options['fields']['field_line_item_description']['field'] = 'field_line_item_description';
  /* Field: Line item: Quantity */
  $handler->display->display_options['fields']['field_line_item_quantity']['id'] = 'field_line_item_quantity';
  $handler->display->display_options['fields']['field_line_item_quantity']['table'] = 'field_data_field_line_item_quantity';
  $handler->display->display_options['fields']['field_line_item_quantity']['field'] = 'field_line_item_quantity';
  $handler->display->display_options['fields']['field_line_item_quantity']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Time unit */
  $handler->display->display_options['fields']['field_line_item_time_unit']['id'] = 'field_line_item_time_unit';
  $handler->display->display_options['fields']['field_line_item_time_unit']['table'] = 'field_data_field_line_item_time_unit';
  $handler->display->display_options['fields']['field_line_item_time_unit']['field'] = 'field_line_item_time_unit';
  /* Field: Line item: Unit cost */
  $handler->display->display_options['fields']['field_line_item_unit_cost']['id'] = 'field_line_item_unit_cost';
  $handler->display->display_options['fields']['field_line_item_unit_cost']['table'] = 'field_data_field_line_item_unit_cost';
  $handler->display->display_options['fields']['field_line_item_unit_cost']['field'] = 'field_line_item_unit_cost';
  $handler->display->display_options['fields']['field_line_item_unit_cost']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Tax */
  $handler->display->display_options['fields']['field_line_item_tax']['id'] = 'field_line_item_tax';
  $handler->display->display_options['fields']['field_line_item_tax']['table'] = 'field_data_field_line_item_tax';
  $handler->display->display_options['fields']['field_line_item_tax']['field'] = 'field_line_item_tax';
  $handler->display->display_options['fields']['field_line_item_tax']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Discount */
  $handler->display->display_options['fields']['field_line_item_discount']['id'] = 'field_line_item_discount';
  $handler->display->display_options['fields']['field_line_item_discount']['table'] = 'field_data_field_line_item_discount';
  $handler->display->display_options['fields']['field_line_item_discount']['field'] = 'field_line_item_discount';
  $handler->display->display_options['fields']['field_line_item_discount']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Line item: Total */
  $handler->display->display_options['fields']['field_line_item_total']['id'] = 'field_line_item_total';
  $handler->display->display_options['fields']['field_line_item_total']['table'] = 'line_item';
  $handler->display->display_options['fields']['field_line_item_total']['field'] = 'field_line_item_total';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Invoice: Invoice ID */
  $handler->display->display_options['arguments']['iid']['id'] = 'iid';
  $handler->display->display_options['arguments']['iid']['table'] = 'invoice';
  $handler->display->display_options['arguments']['iid']['field'] = 'iid';
  $handler->display->display_options['arguments']['iid']['relationship'] = 'reverse_field_invoice_services_invoice';
  $handler->display->display_options['arguments']['iid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['iid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['iid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['iid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['iid']['summary_options']['items_per_page'] = '25';
  $export['line_items'] = $view;

  $view = new view();
  $view->name = 'tax_rates';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'tax_rates';
  $view->human_name = 'Tax rate';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Tax rates';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view own tax rates';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'tid' => 'tid',
    'bid' => 'bid',
    'name' => 'name',
    'rate' => 'rate',
    'edit_tax_rate' => 'edit_tax_rate',
    'delete_tax_rate' => 'delete_tax_rate',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'tid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rate' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_tax_rate' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'delete_tax_rate' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No tax rates found. Please <a href="/settings/tax-rates/add">add a tax rate</a>.';
  /* Relationship: Tax rates: Business */
  $handler->display->display_options['relationships']['tid']['id'] = 'tid';
  $handler->display->display_options['relationships']['tid']['table'] = 'tax_rates';
  $handler->display->display_options['relationships']['tid']['field'] = 'tid';
  $handler->display->display_options['relationships']['tid']['required'] = TRUE;
  /* Field: Tax rates: Tax rate ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'tax_rates';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  /* Field: Tax rates: Business ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'tax_rates';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  $handler->display->display_options['fields']['bid']['label'] = '';
  $handler->display->display_options['fields']['bid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['bid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['bid']['separator'] = '';
  /* Field: Tax rates: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'tax_rates';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Tax rates: Rate */
  $handler->display->display_options['fields']['rate']['id'] = 'rate';
  $handler->display->display_options['fields']['rate']['table'] = 'tax_rates';
  $handler->display->display_options['fields']['rate']['field'] = 'rate';
  /* Field: Tax rates: Edit link */
  $handler->display->display_options['fields']['edit_tax_rate']['id'] = 'edit_tax_rate';
  $handler->display->display_options['fields']['edit_tax_rate']['table'] = 'tax_rates';
  $handler->display->display_options['fields']['edit_tax_rate']['field'] = 'edit_tax_rate';
  $handler->display->display_options['fields']['edit_tax_rate']['label'] = '';
  $handler->display->display_options['fields']['edit_tax_rate']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_tax_rate']['element_label_colon'] = FALSE;
  /* Field: Tax rates: Delete link */
  $handler->display->display_options['fields']['delete_tax_rate']['id'] = 'delete_tax_rate';
  $handler->display->display_options['fields']['delete_tax_rate']['table'] = 'tax_rates';
  $handler->display->display_options['fields']['delete_tax_rate']['field'] = 'delete_tax_rate';
  $handler->display->display_options['fields']['delete_tax_rate']['label'] = '';
  $handler->display->display_options['fields']['delete_tax_rate']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_tax_rate']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<ul class="links inline"><li class="edit first">[edit_tax_rate]</li><li class="delete last">[delete_tax_rate]</li></ul>';
  /* Contextual filter: Business: Business ID */
  $handler->display->display_options['arguments']['bid']['id'] = 'bid';
  $handler->display->display_options['arguments']['bid']['table'] = 'business';
  $handler->display->display_options['arguments']['bid']['field'] = 'bid';
  $handler->display->display_options['arguments']['bid']['relationship'] = 'tid';
  $handler->display->display_options['arguments']['bid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['bid']['default_argument_type'] = 'business_active';
  $handler->display->display_options['arguments']['bid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['bid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['bid']['summary_options']['items_per_page'] = '25';

  /* Display: Tax rates */
  $handler = $view->new_display('page', 'Tax rates', 'page_tax_rates');
  $handler->display->display_options['path'] = 'settings/tax-rates';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Tax rates';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Tax rates';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['tax_rates'] = $view;

  return $export;
}
