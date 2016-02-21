<?php

/**
 * @file
 * Contains invoice_handler_total_field.
 */

/**
 * Field handler to present the invoice total to a client.
 */
class invoice_handler_total_field extends views_handler_field_numeric {

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

    if (!empty($this->options['set_precision'])) {
      $value = number_format($value, $this->options['precision'], $this->options['decimal'], $this->options['separator']);
    }
    else {
      $remainder = abs($value) - intval(abs($value));
      $value = $value > 0 ? floor($value) : ceil($value);
      $value = number_format($value, 0, '', $this->options['separator']);
      if ($remainder) {
        // The substr may not be locale safe.
        $value .= $this->options['decimal'] . substr($remainder, 2);
      }
    }

    // Check to see if hiding should happen before adding prefix and suffix.
    if ($this->options['hide_empty'] && empty($value) && ($value !== 0 || $this->options['empty_zero'])) {
      return '';
    }

    // Should we format as a plural.
    if (!empty($this->options['format_plural'])) {
      $value = format_plural($value, $this->options['format_plural_singular'], $this->options['format_plural_plural']);
    }

    return $this->sanitize_value($this->options['prefix'], 'xss')
    . $this->sanitize_value($value)
    . $this->sanitize_value($this->options['suffix'], 'xss');
  }

  /**
   * {@inheritdoc}
   */
  public function get_value($values, $field = NULL) {
    $invoice = invoice_load($values->{$this->aliases[$field]});
    return $invoice->getTotal();
  }

}
