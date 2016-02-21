<?php

/**
 * @file
 * Contains line_item_handler_total_field.
 */

/**
 * Field handler to display the total price of a line item.
 */
class line_item_handler_total_field extends views_handler_field {

  /**
   * Constructs a line_item_handler_total_field object.
   */
  public function construct() {
    parent::construct();

    // Make sure the line item ID is available in the query.
    $this->additional_fields['lid'] = 'lid';
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
    $value = $this->get_value($values, 'lid');
    $line_item = line_item_load($value);
    $totals = line_item_calculate($line_item);

    return $totals['total'] . '&euro;';
  }

}
