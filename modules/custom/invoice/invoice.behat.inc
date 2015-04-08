<?php

/**
 * @file
 * Contains \InvoiceSubContext.
 */

use Behat\Gherkin\Node\TableNode;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;

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
  public $invoices = array();

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
   * | client  | number    | date     |
   * | Axemill | 2015/0001 | 20150223 |
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

    foreach ($invoices_table->getHash() as $invoice_hash) {
      $invoice = $this->createInvoice(array(
        'bid' => $businesses[0]->identifier(),
        'field_invoice_client' => $this->getClientByName($invoice_hash['client'])->identifier(),
        'field_invoice_number' => $invoice_hash['number'],
        'field_invoice_date' => strtotime($invoice_hash['date'] . ' 00:00 UTC'),
      ));
      $this->invoices[$invoice_hash['number']] = $invoice;
    }
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
  public function createInvoice(array $values = array()) {
    $invoice = invoice_create();
    $this->updateInvoice($invoice, $values);
    invoice_save($invoice);

    $wrapper = entity_metadata_wrapper('invoice', $invoice);
    $this->invoices[$wrapper->field_invoice_number->value()] = $invoice;

    return $invoice;
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
