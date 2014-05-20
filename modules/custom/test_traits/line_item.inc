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
   * Creates a new line item entity.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return LineItem
   *   A new line item entity.
   */
  function createLineItem(array $values = array()) {
    // Provide some default values.
    $values += $this->randomLineItemValues();
    $line_item = line_item_create(array('type' => $values['type']));
    $this->updateLineItem($line_item, $values);

    return $line_item;
  }

  /**
   * Creates a new line item entity through the user interface.
   *
   * The saved line item is retrieved by the line item number.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return LineItem
   *   A new line item entity.
   */
  function createUiLineItem(array $values = array()) {
    // Provide some default values.
    $values += $this->randomLineItemValues();

    // Convert the entity property values to form values and submit the form.
    $edit = $this->convertToFormPostValues($values);

    // Get the type from the values array and unset afterwards because it is not
    // needed to post it with the other form fields.
    $type = $values['type'];
    unset($values['type']);

    $this->drupalPost('line_item/add/' . $type, $edit, t('Save'));

    // Retrieve the saved line _item by line _item number and return it.
    $query = new EntityFieldQuery();
    $query
      ->entityCondition('entity_type', 'line_item')
      ->entityCondition('bundle', $type)
      ->fieldCondition('field_line_item_description', 'value', $values['field_line_item_description'])
      ->range(0,1);
    $result = $query->execute();
    $lids = array_keys($result['line_item']);
    $this->assertTrue($lids, 'Line_item was successfully created through the UI.');

    return line_item_load($lids[0]);
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

}
