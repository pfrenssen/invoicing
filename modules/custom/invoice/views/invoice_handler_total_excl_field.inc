<?php

/**
 * @file
 * Contains invoice_handler_total_excl_field.
 */

/**
 * Field handler to present the invoice total excluding VAT to a client.
 */
class invoice_handler_total_excl_field extends invoice_handler_total_field {

  /**
   * {@inheritdoc}
   */
  function get_value($values, $field= NULL) {
    $invoice = invoice_load($values->{$this->aliases[$field]});
    return $invoice->getTotalExVat();
  }
}
