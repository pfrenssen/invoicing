<?php

/**
 * @file
 * Contains tax_rate_handler_delete_link_field.
 */

/**
 * Field handler to present a link to delete a tax rate.
 */
class tax_rate_handler_delete_link_field extends tax_rate_handler_link_field {

  /**
   * {@inheritdoc}
   */
  public function render_link($tax_rate, $values) {
    if (tax_rate_access('delete', $tax_rate)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "business-preferences/tax-rates/$tax_rate->tid/delete";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
      return $text;
    }
  }

}
