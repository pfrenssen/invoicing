<?php

/**
 * @file
 * Base class for testing the Client module.
 */

class ClientWebTestCase extends DrupalWebTestCase {

  /**
   * {@inheritdoc}
   */
  protected $profile = 'testing';

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setup('client');
  }

  /**
   * {@inheritdoc}
   *
   * Like DrupalTestCase::randomString(), but includes additional special
   * characters, and starts with a space. This helps in discovering security
   * problems and improper trimming and encoding of strings.
   *
   * By default it returns 16 characters rather than the usual 8 to make up for
   * lost entropy.
   */
  public static function randomString($length = 16) {
    $str = ' &\/;<>\'"ä☢';
    for ($i = 0; $i < $length; $i++) {
      $str .= chr(mt_rand(32, 126));
    }
    return $str;
  }

  /**
   * Returns random values for all properties on the client entity.
   *
   * @returns array
   *   An associative array of random values, keyed by property name.
   */
  public function randomClientValues() {
    return array(
      'name' => $this->randomName(),
      'field_client_address' => $this->randomAddressField(),
      'field_client_shipping_address' => $this->randomAddressField(),
      'field_client_email' => $this->randomEmail(),
      'field_client_notes' => $this->randomString(),
      'field_client_phone' => $this->randomString(),
      'field_client_vat' => $this->randomString(),
    );
  }

  /**
   * Returns a random address field.
   *
   * @return array
   *   A random address field.
   */
  public function randomAddressField() {
    return array(
      'country' => chr(mt_rand(65, 90)) . chr(mt_rand(65, 90)),
      'locality' => $this->randomString(),
      'postal_code' => rand(1000, 9999),
      'thoroughfare' => $this->randomString(),
    );
  }

  /**
   * Returns a random email address.
   *
   * @return string
   *   A random email address.
   */
  public function randomEmail() {
    return strtolower($this->randomName()) . '@example.com';
  }

  /**
   * Check if the client database table is empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  public function assertClientTableEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('client', 'c')->fields('c')->execute()->fetchAll();
    return $this->assertFalse($result, $message ?: 'The client database table is empty.', $group);
  }

  /**
   * Check if the client database table is not empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  public function assertClientTableNotEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('client', 'c')->fields('c')->execute()->fetchAll();
    return $this->assertTrue($result, $message ?: 'The client database table is not empty.', $group);
  }

  /**
   * Check if the properties of the given client match the given values.
   *
   * @param Client $client
   *   The Client entity to check.
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
  public function assertClientProperties(Client $client, array $values, $message = '', $group = 'Other') {
    return $this->assertEntityProperties('client', $client, $values, $message, $group);
  }

  /**
   * Check if the properties of the given entity match the given values.
   *
   * @param string $entity_type
   *   The type of the entity.
   * @param Entity $entity
   *   The entity to check.
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
  public function assertEntityProperties($entity_type, Entity $entity, array $values, $message = '', $group = 'Other') {
    $wrapper = entity_metadata_wrapper($entity_type, $entity);

    $result = TRUE;
    foreach ($values as $property => $value) {
      if (is_array($value)) {
        $result &= $this->assertFalse(array_diff($value, $wrapper->$property->value()), format_string('The %property property has the correct value.', array('%property' => $property)));
      }
      else {
        $result &= $this->assertEqual($wrapper->$property->value(), $value, format_string('The %property property has the correct value.', array('%property' => $property)));
      }
    }

    return $this->assertTrue($result, $message ?: format_string('The @entity contains the given values.', array('@entity' => $entity_type)), $group);
  }

  /**
   * Check if the given form fields are indicating that validation failed.
   *
   * This checks for the presence of the 'error' class on the field.
   *
   * @param array $fields
   *   An indexed array of field names that should be checked.
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  public function assertFieldValidationFailed(array $fields, $message = '', $group = 'Other') {
    $result = TRUE;
    foreach ($fields as $field) {
      $xpath = '//textarea[@name=:value and contains(@class, "error")]|//input[@name=:value and contains(@class, "error")]|//select[@name=:value and contains(@class, "error")]';
      $elements = $this->xpath($this->buildXPathQuery($xpath, array(':value' => $field)));
      $result &= $this->assertTrue($elements, format_string('The field %field has the "error" class.', array('%field' => $field)));
    }
    return $this->assertTrue($result, $message ?: 'All fields are indicating that validation failed.', $group);
  }

  /**
   * Creates a new client entity.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return Client
   *   A new client entity.
   */
  public function createClient(array $values = array()) {
    // Provide some default values.
    $values += $this->randomClientValues();
    $client = client_create();
    $this->updateClient($client, $values);

    return $client;
  }

  /**
   * Creates a new client entity through the user interface.
   *
   * The saved client is retrieved by client name and email address. In order to
   * retrieve the correct client entity, these should be unique.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return Client
   *   A new client entity.
   */
  function createUiClient(array $values = array()) {
    // Provide some default values.
    $values += $this->randomClientValues();

    // Convert the entity property values to form values and submit the form.
    $edit = $this->convertToFormPostValues($values);
    $this->drupalPost('client/add', $edit, t('Save'));

    // Retrieve the saved client by name and email address and return it.
    $query = new EntityFieldQuery();
    $query
      ->entityCondition('entity_type', 'client')
      ->entityCondition('bundle', 'client')
      ->propertyCondition('name', $values['name'])
      ->fieldCondition('field_client_email', 'email', $values['field_client_email'])
      ->range(0,1);
    $result = $query->execute();
    $cids = array_keys($result['client']);
    $this->assertTrue($cids, 'Client was successfully created through the UI.');

    return client_load($cids[0]);
  }

  /**
   * Updates the given client with the given properties.
   *
   * @param Client $client
   *   The client entity to update.
   * @param array $values
   *   An associative array of values to apply to the entity, keyed by property
   *   name.
   */
  public function updateClient(Client $client, array $values) {
    $wrapper = entity_metadata_wrapper('client', $client);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
  }

}
