<?php

/**
 * @file
 * Asserts and helper methods concerning the line item module.
 */

trait LineItemTestHelper {

  /**
   * Check if the properties of the given line item match the given values.
   *
   * @param LineItem $line_item
   *   The line item entity to check.
   * @param array $values
   *   An associative array of values to check, keyed by property name.
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertLineItemProperties(LineItem $line_item, array $values, $message = '', $group = 'Other') {
    if (isset($values['type'])) {
      unset($values['type']);
    }
    return $this->assertEntityProperties('line_item', $line_item, $values, $message, $group);
  }

  /**
   * Check if the line item database table is empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertLineItemTableEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('line_item', 'li')->fields('li')->execute()->fetchAll();
    return $this->assertFalse($result, $message ?: 'The line item database table is empty.', $group);
  }

  /**
   * Check if the line item database table is not empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertLineItemTableNotEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('line_item', 'li')->fields('li')->execute()->fetchAll();
    return $this->assertTrue($result, $message ?: 'The line item database table is not empty.', $group);
  }

  /**
   * Returns a newly created line item entity without saving it.
   *
   * This is intended for unit tests. It will not set a business ID. If you are
   * doing a functionality test use $this->createUiLineItem() instead.
   *
   * @param string $type
   *   Optional line item type, either 'product' or 'service'.
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return LineItem
   *   A new line item entity.
   */
  function createLineItem($type = NULL, array $values = array()) {
    // Provide some default values.
    $type = $type ?: $this->randomType();
    $values += $this->randomLineItemValues($type);
    $line_item = line_item_create(array('type' => $values['type']));
    $this->updateLineItem($line_item, $values);

    return $line_item;
  }

  /**
   * Returns random values for all properties on the line item entity.
   *
   * @param string $type
   *   The type of the line item.
   *
   * @returns array
   *   An associative array of random values, keyed by property name.
   */
  function randomLineItemValues($type = NULL) {
    if (empty($type)) {
      $type = $this->randomType();
    }

    $values =  array(
      'field_line_item_description' => $this->randomString(),
      'field_line_item_discount' => $this->randomDecimal(),
      'field_line_item_quantity' => $this->randomDecimal(),
      'field_line_item_tax' => $this->randomDecimal(),
      'field_line_item_unit_cost' => $this->randomDecimal(),
      'type' => $type,
    );

    if ($type == 'service') {
      $values['field_line_item_time_unit'] = array_rand(array(
        'minutes' => 'minutes',
        'hours' => 'hours',
        'days' => 'days',
        'weeks' => 'weeks',
        'months' => 'months',
        'years' => 'years',
      ));
    }

    return $values;
  }

  /**
   * Generate the type for the line item.
   *
   * @return string
   *   The line item type.
   */
  function randomType() {
    return array_rand(array(
      'product' => 'Product',
      'service' => 'Service',
    ));
  }

  /**
   * Generate a random decimal number.
   *
   * @return decimal
   *   A random generated decimal number.
   */
  function randomDecimal() {
    return rand(0, 99) . '.' . rand(0, 99);
  }

  /**
   * Updates the given line item with the given properties.
   *
   * @param LineItem $line_item
   *   The line item entity to update.
   * @param array $values
   *   An associative array of values to apply to the entity, keyed by property
   *   name.
   */
  function updateLineItem(LineItem $line_item, array $values) {
    if (isset($values['type'])) {
      if ($values['type'] == 'product' && isset($values['field_line_item_time_unit'])) {
        unset($values['field_line_item_time_unit']);
      }
      unset($values['type']);
    }

    $wrapper = entity_metadata_wrapper('line_item', $line_item);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
  }

  /**
   * Returns a random line item from the database.
   *
   * @param string $type
   *   Optional line item type. Either 'product' or 'service'.
   *
   * @return LineItem
   *   A random line item.
   */
  function randomLineItem($type = NULL) {
    $query = db_select('line_item', 'li')
      ->fields('li', array('lid'))
      ->orderRandom()
      ->range(0, 1);

    if ($type) {
      $query->condition('type', $type);
    }

    $lid = $query->execute()
      ->fetchColumn();

    return line_item_load($lid);
  }

}
