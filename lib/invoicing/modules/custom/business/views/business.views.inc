<?php

/**
 * @file
 * Provide views data and handlers for the Business module.
 */

/**
 * Implements hook_views_plugins().
 */
function business_views_plugins() {
  return array(
    'argument default' => array(
      'business_active' => array(
        'title' => t('Active business'),
        'handler' => 'views_plugin_argument_default_business_active',
      ),
    ),
  );
}
