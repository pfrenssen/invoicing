<?php
/**
 * @file
 * invoice.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function invoice_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'client_detail';
  $page->task = 'page';
  $page->admin_title = 'Client detail';
  $page->admin_description = '';
  $page->path = 'client/%client/view';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'client_crud_access',
        'settings' => array(
          'operation' => 'view',
        ),
        'context' => 'argument_entity_id:client_1',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'default tab',
    'title' => 'View',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => 'dapare',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'client' => array(
      'id' => 1,
      'identifier' => 'Client: ID',
      'name' => 'entity_id:client',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_client_detail_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'client_detail';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Default',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%client:name';
  $display->uuid = 'd2720c13-14f9-46d2-9dda-de72360541cc';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-902793e8-84b1-4b65-af58-26230e138462';
    $pane->panel = 'middle';
    $pane->type = 'entity_view';
    $pane->subtype = 'client';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'default',
      'context' => 'argument_entity_id:client_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '902793e8-84b1-4b65-af58-26230e138462';
    $display->content['new-902793e8-84b1-4b65-af58-26230e138462'] = $pane;
    $display->panels['middle'][0] = 'new-902793e8-84b1-4b65-af58-26230e138462';
    $pane = new stdClass();
    $pane->pid = 'new-744f8e6a-86ca-4abc-b7ec-c66820a576e8';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'invoices-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:client_1',
      ),
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '744f8e6a-86ca-4abc-b7ec-c66820a576e8';
    $display->content['new-744f8e6a-86ca-4abc-b7ec-c66820a576e8'] = $pane;
    $display->panels['middle'][1] = 'new-744f8e6a-86ca-4abc-b7ec-c66820a576e8';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-902793e8-84b1-4b65-af58-26230e138462';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['client_detail'] = $page;

  return $pages;

}
