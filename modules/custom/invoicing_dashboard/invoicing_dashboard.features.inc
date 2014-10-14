<?php
/**
 * @file
 * invoicing_dashboard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function invoicing_dashboard_ctools_plugin_api($module = NULL, $api = NULL) {
  $plugins = array(
    'page_manager:pages_default',
    'strongarm:strongarm',
  );

  if (in_array("$module:$api", $plugins)) {
    return array("version" => "1");
  }
}
