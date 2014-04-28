<?php

/**
 * @file
 * Asserts and helper methods for testing Business functionality.
 */

trait BusinessTestHelper {

  /**
   * Check if the properties of the given business match the given values.
   *
   * @param business $business
   *   The Business entity to check.
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
  function assertBusinessProperties(Business $business, array $values, $message = '', $group = 'Other') {
    return $this->assertEntityProperties('business', $business, $values, $message, $group);
  }

  /**
   * Check if the business database table is empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertBusinessTableEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('business', 'b')->fields('b')->execute()->fetchAll();
    return $this->assertFalse($result, $message ?: 'The business database table is empty.', $group);
  }

  /**
   * Check if the business database table is not empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertBusinessTableNotEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('business', 'b')->fields('b')->execute()->fetchAll();
    return $this->assertTrue($result, $message ?: 'The business database table is not empty.', $group);
  }

  /**
   * Creates a new business entity.
   *
   * The business only is created and returned, it is not saved.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return Business
   *   A new business entity.
   */
  function createBusiness(array $values = array()) {
    // Provide some default values.
    $values += $this->randomBusinessValues();
    $business = business_create();
    $this->updateBusiness($business, $values);

    return $business;
  }

  /**
   * Creates a new business entity through the user interface.
   *
   * The saved business is retrieved by business name and email address. In
   * order to retrieve the correct business entity, these should be unique.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return Business
   *   A new business entity.
   */
  function createUiBusiness(array $values = array()) {
    // Provide some default values.
    $values += $this->randomBusinessValues();

    // Convert the entity property values to form values and submit the form.
    $edit = $this->convertBusinessValuesToFormPostValues($values);
    $this->drupalPost('business/add', $edit, t('Save'));

    // Retrieve the saved business by name and email address and return it.
    $query = new EntityFieldQuery();
    $query
      ->entityCondition('entity_type', 'business')
      ->entityCondition('bundle', 'business')
      ->propertyCondition('name', $values['name'])
      ->fieldCondition('field_business_email', 'email', $values['field_business_email'])
      ->range(0,1);
    $result = $query->execute();
    $bids = array_keys($result['business']);
    $this->assertTrue($bids, 'Business was successfully created through the UI.');

    return business_load($bids[0]);
  }

  /**
   * Returns random values for all properties on the business entity.
   *
   * @returns array
   *   An associative array of random values, keyed by property name.
   */
  function randomBusinessValues() {
    return array(
      'name' => $this->randomName(),
      'field_business_address' => $this->randomAddressField(),
      'field_business_bic' => $this->randomString(),
      'field_business_email' => $this->randomEmail(),
      'field_business_iban' => $this->randomString(),
      'field_business_mobile' => $this->randomString(),
      'field_business_phone' => $this->randomString(),
      'field_business_vat' => $this->randomString(),
    );
  }

  /**
   * Returns form post values from the given entity values.
   *
   * @see self::randomBusinessValues()
   *
   * @param array $values
   *   An associative array of business values, keyed by property name, as
   *   returned by self::randomBusinessValues().
   *
   * @returns array
   *   An associative array of values, keyed by form field name, as used by
   *   parent::drupalPost().
   */
  public function convertBusinessValuesToFormPostValues($values) {
    return array(
      'name' => $values['name'],
      'field_business_email[und][0][email]' => $values['field_business_email'],
      // @todo Support other countries in addition to Belgium.
      'field_business_address[und][0][country]' => 'BE',
      'field_business_address[und][0][thoroughfare]' => $values['field_business_address']['thoroughfare'],
      'field_business_address[und][0][postal_code]' => $values['field_business_address']['postal_code'],
      'field_business_address[und][0][locality]' => $values['field_business_address']['locality'],
      'field_business_vat[und][0][value]' => $values['field_business_vat'],
      'field_business_phone[und][0][value]' => $values['field_business_phone'],
      'field_business_mobile[und][0][value]' => $values['field_business_mobile'],
      'field_business_bic[und][0][value]' => $values['field_business_bic'],
      'field_business_iban[und][0][value]' => $values['field_business_iban'],
    );
  }

  /**
   * Updates the given business with the given properties.
   *
   * @param Business $business
   *   The business entity to update.
   * @param array $values
   *   An associative array of values to apply to the entity, keyed by property
   *   name.
   */
  function updateBusiness(Business $business, array $values) {
    $wrapper = entity_metadata_wrapper('business', $business);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
  }

}
