<?php

/**
 * @file
 * Contains client_handler_edit_link_field.
 */

/**
 * Field handler to present a link to the edit form of a client.
 */
class client_handler_edit_link_field extends client_handler_link_field {

  /**
   * {@inheritdoc}
   */
  public function render_link(Client $client, \stdClass $values) {
    if (client_access('edit', $client)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "client/$client->cid/edit";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
      return $text;
    }
  }

}
