<?php

/**
 * @file
 * Base class for testing the Client module.
 */

class ClientTestCase extends DrupalWebTestCase {

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

}
