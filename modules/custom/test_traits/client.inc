<?php

/**
 * @file
 * Asserts and helper methods concerning the client module.
 */

trait ClientTestHelper {

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
  function assertClientProperties(Client $client, array $values, $message = '', $group = 'Other') {
    return $this->assertEntityProperties('client', $client, $values, $message, $group);
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
  function assertClientTableEmpty($message = '', $group = 'Other') {
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
  function assertClientTableNotEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('client', 'c')->fields('c')->execute()->fetchAll();
    return $this->assertTrue($result, $message ?: 'The client database table is not empty.', $group);
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
  function createClient(array $values = array()) {
    // Provide some default values.
    $values += $this->randomClientValues();

    // Creating an empty client and then updating the properties through the
    // entity metadata wrapper is easier than $field[LANGUAGE_NONE][0][...].
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
    $edit = $this->convertClientValuesToFormPostValues($values);
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
   * Returns random values for all properties on the client entity.
   *
   * These include the fields from the 'client' bundle.
   *
   * @returns array
   *   An associative array of random values, keyed by property name.
   */
  function randomClientValues() {
    return array(
      'name' => $this->randomString(),
      'field_client_address' => $this->randomAddressField(),
      'field_client_shipping_address' => $this->randomAddressField(),
      'field_client_email' => $this->randomEmail(),
      'field_client_notes' => $this->randomString(),
      'field_client_phone' => $this->randomString(),
      'field_client_vat' => $this->randomString(),
      'field_client_website' => array(
        'url' => 'http://www.test.be',
        'title' => NULL,
        'attributes' => '',
      ),
    );
  }

  /**
   * Returns form post values from the given entity values.
   *
   * @see self::randomClientValues()
   *
   * @param array $values
   *   An associative array of client values, keyed by property name, as
   *   returned by self::randomClientValues().
   *
   * @returns array
   *   An associative array of values, keyed by form field name, as used by
   *   parent::drupalPost().
   */
  public function convertClientValuesToFormPostValues($values) {
    return array(
      'name' => $values['name'],
      'field_client_email[und][0][email]' => $values['field_client_email'],
      // @todo Support other countries in addition to Belgium.
      'field_client_address[und][0][country]' => 'BE',
      'field_client_address[und][0][thoroughfare]' => $values['field_client_address']['thoroughfare'],
      'field_client_address[und][0][postal_code]' => $values['field_client_address']['postal_code'],
      'field_client_address[und][0][locality]' => $values['field_client_address']['locality'],
      // @todo Support other countries in addition to Belgium.
      'field_client_shipping_address[und][0][country]' => 'BE',
      'field_client_shipping_address[und][0][thoroughfare]' => $values['field_client_shipping_address']['thoroughfare'],
      'field_client_shipping_address[und][0][postal_code]' => $values['field_client_shipping_address']['postal_code'],
      'field_client_shipping_address[und][0][locality]' => $values['field_client_shipping_address']['locality'],
      'field_client_vat[und][0][value]' => $values['field_client_vat'],
      'field_client_phone[und][0][value]' => $values['field_client_phone'],
      'field_client_notes[und][0][value]' => $values['field_client_notes'],
      'field_client_website[und][0][url]' => $values['field_client_website']['url'],
    );
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
  function updateClient(Client $client, array $values) {
    $wrapper = entity_metadata_wrapper('client', $client);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
  }

}
