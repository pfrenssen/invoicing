<?php
/**
 * @file
 * invoicing_dashboard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function invoicing_dashboard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }

  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
