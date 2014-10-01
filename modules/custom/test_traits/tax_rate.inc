<?php

/**
 * @file
 * Asserts and helper methods concerning the tax rate module.
 */

trait TaxRateTestHelper {

  /**
   * Check if the properties of the given tax rate match the given values.
   *
   * @param TaxRate $tax_rate
   *   The tax rate entity to check.
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
  function assertTaxRateProperties(TaxRate $tax_rate, array $values, $message = '', $group = 'Other') {
    if (isset($values['type'])) {
      unset($values['type']);
    }
    return $this->assertEntityProperties('tax_rate', $tax_rate, $values, $message, $group);
  }

  /**
   * Check if the tax rate database table is empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertTaxRateTableEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('tax_rate', 'tr')->fields('tr')->execute()->fetchAll();
    return $this->assertFalse($result, $message ?: 'The tax rate database table is empty.', $group);
  }

  /**
   * Check if the tax rate database table is not empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertTaxRateTableNotEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('tax_rate', 'tr')->fields('tr')->execute()->fetchAll();
    return $this->assertTrue($result, $message ?: 'The tax rate database table is not empty.', $group);
  }

  /**
   * Returns a newly created tax rate entity without saving it.
   *
   * This is intended for unit tests. It will not set a business ID. If you are
   * doing a functionality test use $this->createUiTaxRate() instead.
   *
   * @param string $type
   *   Optional tax rate type.
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return TaxRate
   *   A new tax rate entity.
   */
  function createTaxRate($type = NULL, array $values = array()) {
    // Provide some default values.
    $type = $type ?: $this->randomTaxRateType();
    $values += $this->randomTaxRateValues($type);
    $tax_rate = tax_rate_create(array('type' => $values['type']));
    $this->updateTaxRate($tax_rate, $values);

    return $tax_rate;
  }

  /**
   * Returns random values for all properties on the tax rate entity.
   *
   * @param string $type
   *   The type of the tax rate.
   *
   * @returns array
   *   An associative array of random values, keyed by property name.
   */
  function randomTaxRateValues($type = NULL) {
    if (empty($type)) {
      $type = $this->randomTaxRateType();
    }

    $values = array(
      'field_tax_rate_name' => $this->randomString(),
      'field_tax_rate_rate' => $this->randomDecimal(),
      'type' => $type,
    );

    return $values;
  }

  /**
   * Generate the type for the tax rate.
   *
   * @return string
   *   The tax rate type.
   */
  function randomTaxRateType() {
    return array_rand($this->getTaxRateTypes());
  }

  /**
   * Returns the supported tax rate types.
   *
   * @return array
   *   An associative array of tax rate names, keyed by bundle name.
   */
  public function getTaxRateTypes() {
    return array(
      'tax_rate' => t('Tax rate'),
    );
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
   * Updates the given tax rate with the given properties.
   *
   * @param TaxRate $tax_rate
   *   The tax rate entity to update.
   * @param array $values
   *   An associative array of values to apply to the entity, keyed by property
   *   name.
   */
  function updateTaxRate(TaxRate $tax_rate, array $values) {
    if (isset($values['type'])) {
      unset($values['type']);
    }

    $wrapper = entity_metadata_wrapper('tax_rate', $tax_rate);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
  }

  /**
   * Returns a random tax rate from the database.
   *
   * @param string $type
   *   Optional tax rate type..
   *
   * @return TaxRate
   *   A random tax rate.
   */
  function randomTaxRate($type = NULL) {
    $query = db_select('tax_rate', 'tr')
      ->fields('tr', array('tid'))
      ->orderRandom()
      ->range(0, 1);

    if ($type) {
      $query->condition('type', $type);
    }

    $tid = $query->execute()
      ->fetchColumn();

    return tax_rate_load($tid);
  }

  /**
   * Returns random data for the basic tax rate properties.
   *
   * These are values for the properties that are present on every tax rate
   * entity regardless of the bundle type.
   *
   * This excludes the tax rate ID ('tid') which is immutable.
   *
   * @return array
   *   An associative array of property values, keyed by property name.
   */
  protected function randomTaxRatePropertyValues() {
    return array(
      'type' => $this->randomName(),
      'bid' => $this->randomBusiness()->identifier(),
      'created' => rand(0, 2000000000),
      'changed' => rand(0, 2000000000),
    );
  }

   /**
   * Returns random field data for the fields in the tax rate entity.
   *
   * @returns array
   *   An associative array of field data, keyed by field name.
   */
  public function randomTaxRateFieldValues() {
    $values = array();

    $values['field_tax_rate_name'][LANGUAGE_NONE][0]['value'] = $this->randomString();
    $values['field_tax_rate_rate'][LANGUAGE_NONE][0]['value'] = $this->randomString();

    return $values;
  }
}
