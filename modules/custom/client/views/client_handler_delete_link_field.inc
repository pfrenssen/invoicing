<?php

/**
 * @file
 * Contains client_handler_delete_link_field.
 */

/**
 * Field handler to present a link to delete a client.
 */
class client_handler_delete_link_field extends client_handler_link_field {

  /**
   * {@inheritdoc}
   */
  public function render_link($client, $values) {
    if (client_access('delete', $client)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "client/$client->cid/delete";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
      return $text;
    }
  }

}
