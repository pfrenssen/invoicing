<?php

/**
 * @file
 * Contains invoice_handler_total_field.
 */

/**
 * Field handler to present the invoice total to a client.
 */
class invoice_handler_total_field extends views_handler_field {

  /**
   * Constructs a invoice_handler_total_field object.
   */
  public function construct() {
    parent::construct();

    // Make sure the invoice id is available in the query.
    $this->additional_fields['iid'] = 'iid';
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    // Make sure the table and additional fields are added to the query.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    // Get the Invoice total and render it.
    $value = $this->get_value($values, 'iid');

    return $this->sanitize_value($value) . '&euro;';
  }

  /**
   * {@inheritdoc}
   */
  public function get_value($values, $field = NULL) {
    $invoice = invoice_load($values->{$this->aliases[$field]});
    return $invoice->getTotal();
  }

}
