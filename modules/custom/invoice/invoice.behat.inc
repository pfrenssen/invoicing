<?php

/**
 * @file
 * Contains \InvoiceSubContext.
 */

use Behat\Gherkin\Node\TableNode;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Symfony\Component\DomCrawler\Crawler;

/**
 * Behat step definitions for testing invoices.
 */
class InvoiceSubContext extends DrupalSubContextBase implements DrupalSubContextInterface {

  use Drupal\invoicing\Traits\BaseTestHelper;
  use Drupal\invoicing\Traits\ClientTestHelper;
  use Drupal\invoicing\Traits\InvoiceTestHelper;
  use Drupal\invoicing\Traits\LineItemTestHelper;

  /**
   * Test invoices.
   *
   * @var \Invoice[]
   */
  protected $invoices = [];

  /**
   * An exported invoice in HTML format.
   *
   * @var string
   */
  protected $exportedInvoice;

  /**
   * Maps human readable field names to CSS selectors in exported invoices.
   *
   * @var array
   *   An associative array mapping human readable field names to CSS selectors.
   */
  protected $exportedInvoiceSelectors = [
    'client' => '#client-name',
    'client email' => '#client-email .field-item',
    'date' => '#invoice-date .field-item',
    'number' => '#invoice-number .field-item',
  ];

  /**
   * An instance of DomCrawler that can be used to crawl the exported invoice.
   *
   * @var \Symfony\Component\DomCrawler\Crawler
   */
  protected $exportedInvoiceCrawler;

  /**
   * Navigates to the detail page of the invoice with the given number.
   *
   * @When (I )visit the detail page for invoice :number
   */
  public function iAmOnInvoiceDetailPage($number) {
    $invoice = $this->getInvoiceByNumber($number);
    $this->visitPath('/invoice/' . $invoice->identifier());
  }

  /**
   * Navigates to the add invoice form.
   *
   * @When (I )go to the add invoice form
   * @When (I )visit the add invoice form
   */
  public function iAmOnAddInvoiceForm() {
    $this->visitPath('/invoice/add');
  }

  /**
   * Returns the invoice that corresponds with the given invoice number.
   *
   * @param string $invoice_number
   *   The invoice number.
   *
   * @return \Invoice
   *   The desired invoice.
   */
  public function getInvoiceByNumber($invoice_number) {
    return $this->invoices[$invoice_number];
  }

  /**
   * Creates invoices with data provided in a table.
   *
   * Table format:
   * | client | number | date     | products | services   |
   * | Fritz  | 15/001 | 20150223 | Key, Box | Work, Rent |
   *
   * Products and services need to be created before they can be added to an
   * invoice. Multiple products and services can be added comma separated.
   *
   * @param TableNode $invoices_table
   *   The invoice data.
   *
   * @throws \Exception
   *   Thrown when no user is logged in.
   *
   * @Given invoice(s):
   */
  public function createInvoices(TableNode $invoices_table) {
    if (!$this->getUser()->uid) {
      throw new \Exception('There is no current logged in user to create an invoice for.');
    }

    $user = entity_metadata_wrapper('user', user_load($this->getUser()->uid));
    $businesses = $user->field_user_businesses->value();

    if (empty($businesses)) {
      throw new \Exception('Cannot create invoices, the currently logged in user has no business.');
    }

    foreach ($invoices_table->getHash() as $row) {
      // Add required properties.
      $values = [
        'bid' => $businesses[0]->identifier(),
        'field_invoice_client' => $this->getClientByName($row['client'])->identifier(),
        'field_invoice_number' => $row['number'],
        'field_invoice_date' => strtotime($row['date'] . ' 00:00 UTC'),
      ];

      // Add optional line items. Multiple items can be separated by commas.
      foreach (['products', 'services'] as $type) {
        if (array_key_exists($type, $row)) {
          $line_items = array_map('trim', explode(',', $row[$type]));
          foreach ($line_items as $line_item) {
            $values["field_invoice_$type"][] = $this->getLineItem($line_item);
          }
        }
      }

      $invoice = $this->createInvoice($values);
      $this->invoices[$row['number']] = $invoice;
    }
  }

  /**
   * Returns the line item with the given description.
   *
   * This returns line items that are stored on LineItemSubContext. This only
   * contains line items that were created during the current test run.
   *
   * @param string $description
   *   The description of the line item.
   *
   * @return \LineItem
   *   The line item.
   *
   * @throws \InvalidArgumentException
   *   Thrown when no line item with the given description exists.
   */
  protected function getLineItem($description) {
    /** @var \LineItemSubContext $context */
    $context = $this->getContext('LineItemSubContext');
    return $context->getLineItem($description);
  }

  /**
   * Creates a new invoice with the given values.
   *
   * @param array $values
   *   An optional associative array of values, keyed by property name.
   *
   * @return \Invoice
   *   A new invoice entity.
   */
  public function createInvoice(array $values = []) {
    $invoice = invoice_create();
    $this->updateInvoice($invoice, $values);
    invoice_save($invoice);

    $wrapper = entity_metadata_wrapper('invoice', $invoice);
    $this->invoices[$wrapper->field_invoice_number->value()] = $invoice;

    return $invoice;
  }

  /**
   * Creates an HTML export of the invoice with the given number.
   *
   * @param string $number
   *   The invoice number.
   *
   * @When I export the invoice with number :number
   */
  public function exportInvoice($number) {
    $invoice = $this->getInvoiceByNumber($number);
    $this->exportedInvoice = theme('invoice_export', ['invoice' => $invoice]);
    $this->exportedInvoiceCrawler = new Crawler($this->exportedInvoice);
  }

  /**
   * Asserts that the exported invoice contains the given field data.
   *
   * @param \Behat\Gherkin\Node\TableNode $table
   *   The field data.
   *
   * @Then the exported invoice should have the (following )field(s):
   */
  public function assertExportedInvoiceFields(TableNode $table) {
    foreach ($table->getRowsHash() as $field => $value) {
      $this->assertExportedInvoiceField($field, $value);
    }
  }

  /**
   * Asserts that the exported invoice contains the given field.
   *
   * @param string $field
   *   The field name.
   * @param string $value
   *   The expected value for the field.
   *
   * @throws \Exception
   *   Thrown when the field is not present, or the field value does not match.
   */
  public function assertExportedInvoiceField($field, $value) {
    $selector = $this->exportedInvoiceSelectors[$field];
    $field_items = $this->exportedInvoiceCrawler->filter($selector);

    // Check if the field is present in the exported invoice.
    if (!$field_items->count()) {
      throw new \Exception("The '$field' field is not present in the exported invoice.");
    }

    // Loop over the field items and check if the given value is found.
    /** @var \DOMElement $field_item */
    foreach ($field_items as $field_item) {
      if ($field_item->textContent === $value) {
        return;
      }
    }

    // The value was not found, fail the test.
    throw new \Exception("The value '$value' was not found for the '$field' field.");
  }

  /**
   * Returns the client with the given name.
   *
   * @param string $name
   *   The client name.
   *
   * @return \Client
   *   The requested client.
   */
  protected function getClientByName($name) {
    return $this->getContext('ClientSubContext')->clients[$name];
  }

  /**
   * Remove any created invoices.
   *
   * @AfterScenario
   */
  public function cleanInvoices() {
    // Remove any invoices that were created.
    foreach ($this->invoices as $invoice) {
      invoice_delete($invoice);
    }
  }

}
