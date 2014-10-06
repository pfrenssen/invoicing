<?php

/**
 * @file
 * Contains client_handler_edit_link_field.
 */

/**
 * Field handler to present a link to the edit form of a tax rate.
 */
class tax_rate_handler_edit_link_field extends views_handler_field {

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
    if (line_item_tax_rate_access('update', $tax_rate)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "business-preferences/tax-rates/$tax_rate->tid/edit";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
      return $text;
    }
  }

}
