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
   * A test invoice number.
   *
   * @var string
   */
  protected $invoiceNumber;

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
   * | client | number | date     | discount | products | services   |
   * | Fritz  | 15/001 | 20150223 | 10       | Key, Box | Work, Rent |
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
        'field_invoice_discount' => !empty($row['discount']) ? $row['discount'] : 0,
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
   * Checks the number of invoices that the currently logged in user has.
   *
   * @param int $count
   *   The number of invoices the logged in user is supposed to have.
   *
   * @throws \Exception
   *   Thrown when the user is not logged in.
   *
   * @Then I should have :count invoice(s)
   */
  public function assertInvoiceCount($count) {
    if (!$this->getUser()->uid) {
      throw new \Exception('The user is not logged in.');
    }

    $user = user_load($this->getUser()->uid);
    $iids = invoice_get_invoice_ids_from_user($user, TRUE);
    PHPUnit_Framework_Assert::assertEquals($count, count($iids));
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
   * Asserts that the exported invoice contains the given product data.
   *
   * Table format:
   * | description | unit cost | quantity | tax   | discount | total |
   * | Equipment   | 124.95    | 10.5     | 19.00 | 15       | 12    |
   *
   * @param \Behat\Gherkin\Node\TableNode $table
   *   A table containing product data.
   *
   * @Then the exported invoice should have the (following )product data:
   */
  public function assertExportedInvoiceProducts(TableNode $table) {
    foreach ($table->getColumnsHash() as $product) {
      $data = $this->getExportedLineItemData('product', $product['description']);
      $this->assertExportedLineItemData($product, $data);
    }
  }

  /**
   * Asserts that the exported invoice contains the given service data.
   *
   * Table format:
   * | description | unit cost | time unit | quantity | tax   | discount | total |
   * | Equipment   | 124.95    | months    | 10.5     | 19.00 | 15       | 12    |
   *
   * @param \Behat\Gherkin\Node\TableNode $table
   *   A table containing service data.
   *
   * @Then the exported invoice should have the (following )service data:
   */
  public function assertExportedInvoiceServices(TableNode $table) {
    foreach ($table->getColumnsHash() as $service) {
      $data = $this->getExportedLineItemData('service', $service['description']);
      $this->assertExportedLineItemData($service, $data);
    }
  }

  /**
   * Checks if the given exported line item data matches the given line item.
   *
   * @param array $expected
   *   The expected data.
   * @param array $actual
   *   An associative array, keyed by human readable property names, with the
   *   line item data as it appears in the exported invoice.
   *
   * @throws \Exception
   *   Thrown when the actual data does not match the expected data.
   */
  protected function assertExportedLineItemData(array $expected, array $actual) {
    foreach ($expected as $key => $value) {
      PHPUnit_Framework_Assert::assertArrayHasKey($key, $actual);
      PHPUnit_Framework_Assert::assertEquals($value, $actual[$key]);
    }
  }

  /**
   * Returns exported line item data matching the given type and description.
   *
   * @param string $type
   *   The line item type. Either 'product' or 'service'.
   * @param string $description
   *   The line item description.
   *
   * @return array
   *   An associative array with the line item data as it appears in the
   *   exported invoice. With keys 'description', 'quantity', 'unit cost', 'tax'
   *   and 'discount'. Services also have the key 'time unit'.
   *
   * @throws \Exception
   *   Thrown when a table cell is encountered which is not recognized as a line
   *   item Views field.
   */
  protected function getExportedLineItemData($type, $description) {
    $line_item_data = [];

    // Retrieve the parent node of the table cell containing the description.
    // This will be the table row containing the line item.
    $selector = "#${type}s table tbody td.views-field-field-line-item-description";
    $element = $this->getDomElementByCssSelectorAndText($this->exportedInvoiceCrawler, $selector, $description)->parentNode;

    foreach ($element->childNodes as $node) {
      // Only inspect <td> DOM elements, ignore other elements and whitespace.
      if ($node instanceof \DOMElement && $node->tagName === 'td') {
        $classes = $node->getAttribute('class');
        // Retrieve the key from the views field class on the table cell.
        $key = function () use ($classes) {
          foreach (explode(' ', $classes) as $class) {
            if (substr($class, 0, 28) === 'views-field-field-line-item-') {
              // Turn to dashes into spaces to make it human readable.
              return str_replace('-', ' ', substr($class, 28));
            }
          }
          throw new \Exception('The line item table contains a cell which is not a line item Views field.');
        };
        $line_item_data[$key()] = trim($node->textContent);
      }
    }

    return $line_item_data;
  }

  /**
   * Returns the DOM element that matches the given CSS selector and text.
   *
   * @param \Symfony\Component\DomCrawler\Crawler $crawler
   *   An instance of Crawler containing the document to search.
   * @param string $selector
   *   The CSS selector that should match the element.
   * @param string $text
   *   The text that should be present in the element.
   *
   * @return \DOMElement
   *   The matched DOM element.
   *
   * @throws \Exception
   *   Thrown when no DOM element matches the given criteria.
   */
  protected function getDomElementByCssSelectorAndText(Crawler $crawler, $selector, $text) {
    /** @var \DOMElement $dom_element */
    foreach ($crawler->filter($selector) as $dom_element) {
      if (trim($dom_element->textContent) === $text) {
        return $dom_element;
      }
    }
    throw new \Exception("The text '$text' wasn't found in the DOM element identified by '$selector'.'");
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
   * Stores an invoice number.
   *
   * @param string $number
   *   The invoice number.
   *
   * @Given the most recent invoice has the number :number
   */
  public function setInvoiceNumber($number) {
    $this->invoiceNumber = $number;
  }

  /**
   * Asserts that the next invoice number equals the given number.
   *
   * @param string $expected
   *   The expected invoice number.
   *
   * @Then the next invoice number should be :expected
   */
  public function assertNextInvoiceNumber($expected) {
    $actual = invoice_increment_number($this->invoiceNumber);
    PHPUnit_Framework_Assert::assertEquals($expected, $actual);
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

  /**
   * Checks that the price including VAT of an invoice equals the expected total.
   *
   * @param string $number
   *   The description of the line item.
   * @param string $including
   *   The expected price total.
   *
   * @Then the price including VAT of the :number invoice should equal :including
   */
  public function assertInvoicePriceCalculationIncVat($number, $including) {
    $invoice = $this->getInvoiceByNumber($number);
    PHPUnit_Framework_Assert::assertEquals($including, $invoice->getTotal());
  }

  /**
   * Checks that the price excluding VAT of an invoice equals the expected total.
   *
   * @param string $number
   *   The description of the line item.
   * @param string $excluding
   *   The expected price total.
   *
   * @Then the price excluding VAT of the :number invoice should equal :excluding
   */
  public function assertInvoicePriceCalculationExcVat($number, $excluding) {
    $invoice = $this->getInvoiceByNumber($number);
    PHPUnit_Framework_Assert::assertEquals($excluding, $invoice->getTotalExVat());
  }

}
