<?php

/**
 * @file
 * Contains the active business argument default plugin.
 */

/**
 * Default argument plugin to return the bid of the active business.
 */
class views_plugin_argument_default_business_active extends views_plugin_argument_default {

  /**
   * {@inheritdoc}
   */
  public function get_argument() {
    $business = business_get_active_business();
    return !empty($business) ? $business->identifier() : FALSE;
  }

}
