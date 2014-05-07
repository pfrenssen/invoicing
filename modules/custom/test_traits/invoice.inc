<?php

/**
 * @file
 * Asserts and helper methods concerning the invoice module.
 */

trait InvoiceTestHelper {

  /**
   * Check if the properties of the given invoice match the given values.
   *
   * @param Invoice $invoice
   *   The Invoice entity to check.
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
  function assertInvoiceProperties(Invoice $invoice, array $values, $message = '', $group = 'Other') {
    return $this->assertEntityProperties('invoice', $invoice, $values, $message, $group);
  }

  /**
   * Check if the invoice database table is empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertInvoiceTableEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('invoice', 'i')->fields('i')->execute()->fetchAll();
    return $this->assertFalse($result, $message ?: 'The invoice database table is empty.', $group);
  }

  /**
   * Check if the invoice database table is not empty.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertInvoiceTableNotEmpty($message = '', $group = 'Other') {
    $result = (bool) db_select('invoice', 'i')->fields('i')->execute()->fetchAll();
    return $this->assertTrue($result, $message ?: 'The invoice database table is not empty.', $group);
  }

  /**
   * Creates a new invoice entity.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return Invoice
   *   A new invoice entity.
   */
  function createInvoice(array $values = array()) {
    // Provide some default values.
    $values += $this->randomInvoiceValues();
    $invoice = invoice_create();
    $this->updateInvoice($invoice, $values);

    return $invoice;
  }

  /**
   * Creates a new invoice entity through the user interface.
   *
   * The saved invoice is retrieved by the invoice number.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name. Random
   *   values will be applied to all omitted properties.
   *
   * @return Invoice
   *   A new invoice entity.
   */
  function createUiInvoice(array $values = array()) {
    // Provide some default values.
    $values += $this->randomInvoiceValues();

    // Convert the entity property values to form values and submit the form.
    $edit = $this->convertInvoiceValuesToFormPostValues($values);
    $this->drupalPost('invoice/add', $edit, t('Save'));

    // Retrieve the saved invoice by invoice number and return it.
    $query = new EntityFieldQuery();
    $query
      ->entityCondition('entity_type', 'invoice')
      ->entityCondition('bundle', 'invoice')
      ->fieldCondition('field_invoice_number', 'value', $values['field_invoice_number'])
      ->range(0,1);
    $result = $query->execute();
    $iids = array_keys($result['invoice']);
    $this->assertTrue($iids, 'Invoice was successfully created through the UI.');

    return invoice_load($iids[0]);
  }

  /**
   * Returns random values for all properties on the invoice entity.
   *
   * This does not include the client reference. This should be provided by the
   * test itself.
   *
   * @return array
   *   An associative array of random values, keyed by property name.
   */
  function randomInvoiceValues() {
    $date_polarity = rand(0, 1) ? '-' : '+';
    $date_offset = rand(0, 7);
    return array(
      'field_invoice_date' => strtotime($date_polarity . $date_offset . ' day 00:00'),
      'field_invoice_number' => $this->randomString(),
      'field_invoice_discount' => rand(0, 100),
      'field_invoice_po_number' => $this->randomString(),
      'field_invoice_due_date' => array_rand(array(
        '0' => 'due on receipt',
        '7' => '7 days',
        '15' => '15 days',
        '30' => '30 days',
        '60' => '60 days',
      )),
      'field_invoice_terms' => $this->randomString(),
      'field_invoice_status' => array_rand(array(
        'draft' => 'draft',
        'sent' => 'sent',
      ))
    );
  }

  /**
   * Returns form post values from the given entity values.
   *
   * @see self::randomInvoiceValues()
   *
   * @param array $values
   *   An associative array of invoice values, keyed by property name, as
   *   returned by self::randomInvoiceValues().
   *
   * @returns array
   *   An associative array of values, keyed by form field name, as used by
   *   parent::drupalPost().
   */
  public function convertInvoiceValuesToFormPostValues($values) {
    $client = client_load($values['field_invoice_client']);

    return array(
      'field_invoice_client[und]' => $client->name . ' (' . $values['field_invoice_client'] . ')',
      'field_invoice_number[und][0][value]' => $values['field_invoice_number'],
      'field_invoice_date[und][0][value][month]' => date('n', $values['field_invoice_date']),
      'field_invoice_date[und][0][value][day]' => date('j', $values['field_invoice_date']),
      'field_invoice_date[und][0][value][year]' => date('Y', $values['field_invoice_date']),
      'field_invoice_discount[und][0][value]' => $values['field_invoice_discount'],
      'field_invoice_po_number[und][0][value]' => $values['field_invoice_po_number'],
      'field_invoice_due_date[und]' => $values['field_invoice_due_date'],
      'field_invoice_terms[und][0][value]' => $values['field_invoice_terms'],
      'field_invoice_status[und]' => $values['field_invoice_status'],
    );
  }

  /**
   * Updates the given invoice with the given properties.
   *
   * @param Invoice $invoice
   *   The invoice entity to update.
   * @param array $values
   *   An associative array of values to apply to the entity, keyed by property
   *   name.
   */
  function updateInvoice(Invoice $invoice, array $values) {
    $wrapper = entity_metadata_wrapper('invoice', $invoice);
    foreach ($values as $property => $value) {
      $wrapper->$property->set($value);
    }
  }

}
