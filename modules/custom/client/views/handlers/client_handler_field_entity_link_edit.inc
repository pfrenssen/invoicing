<?php

/**
 * @file
 * Definition of client_handler_field_entity_link_edit.
 */

/**
 * Field handler to present a link entity edit.
 *
 * @ingroup views_handler_field_node_link
 */
class client_handler_field_entity_link_edit extends views_handler_field_node_link {

  /**
   * Renders the link.
   */
  function render_link($entity, $values) {
    dsm($entity);
    // Ensure user has access to edit this node.
//    if (!node_access('update', $node)) {
//      return;
//    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/edit";
    if (!empty($this->options['destination']) || !isset($this->options['destination'])) {
      $this->options['alter']['query'] = drupal_get_destination();
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return $text;
  }
}
