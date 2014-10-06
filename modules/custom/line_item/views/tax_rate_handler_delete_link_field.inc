<?php

/**
 * @file
 * Contains client_handler_delete_link_field.
 */

/**
 * Field handler to present a link to delete a tax rate.
 */
class tax_rate_handler_delete_link_field extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    // Default to 'view' if no link text is specified.
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');

    // Return a link to the client.
    $tax_rate = line_item_tax_rate_load($values->{$this->aliases['tid']});

    return $this->render_link($tax_rate, $values);
  }

  /**
   * {@inheritdoc}
   */
  public function render_link($tax_rate, $values) {
    if (line_item_tax_rate_access('delete', $tax_rate)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "business-preferences/tax-rates/$tax_rate->tid/delete";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
      return $text;
    }
  }

}
