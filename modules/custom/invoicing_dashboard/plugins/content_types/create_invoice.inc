<?php

/**
 * @file
 * CTools content type plugin to display an add invoice pane.
 */

$plugin = array(
  'title' => t('Create invoice'),
  'description' => t('Display the "create invoice" link in a pane.'),
  'category' => array(t('Invoicing dashboard'), 0),
  'single' => TRUE,
  'no title override' => TRUE,
);

/**
 * Renders the pane.
 */
function invoicing_dashboard_add_invoice_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = '';
  $block->content= '';

  if (user_access('administer invoices') || user_access('create new invoices')) {
    $block->content = l(t('Create invoice'), 'invoice/add');
  }

  return $block;
}

/**
 * Configuration form for the pane.
 */
function invoicing_dashboard_add_invoice_content_type_edit_form($form, &$form_state) {
  return $form;
}
