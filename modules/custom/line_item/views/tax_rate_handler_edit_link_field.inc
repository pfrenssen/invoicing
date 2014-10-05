<?php

/**
 * @file
 * Contains client_handler_edit_link_field.
 */

/**
 * Field handler to present a link to the edit form of a tax rate.
 */
class tax_rate_handler_edit_link_field extends tax_rate_handler_link_field {

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
