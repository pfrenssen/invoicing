<?php

/**
 * @file
 * Definition of client_handler_field_client_edit_link.
 */

/**
 * Field handler to present a link entity edit.
 *
 * @ingroup views_handler_field_node_link
 */
class client_handler_field_client_edit_link extends views_handler_field_node_link {

  /**
   * Renders the link.
   */
  public function render($values) {
    dsm($values);
    return 'lol';
  }
}
