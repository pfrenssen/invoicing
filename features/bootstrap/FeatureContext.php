<?php

/**
 * @file
 * Contains \FeatureContext.
 */

use Behat\Behat\Context\SnippetAcceptingContext;
use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Generic step definitions for the Invoicing project.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  /**
   * Checks that the current page overview contains a given legend fieldset.
   *
   * @Then I should see( a) fieldset with the legend :legend
   */
  public function iShouldSeeFieldsetWithTheLegend($legend) {
    $mapping = array(
      'Client' => 'edit-field-invoice-client',
      'Add new client' => 'edit-field-invoice-client',
      'Add existing client' => 'edit-field-invoice-client',
      'Services' => 'edit-field-invoice-services',
      'Add new service' => 'edit-field-invoice-services',
      'Add existing service' => 'edit-field-invoice-services',
      'Products' => 'edit-field-invoice-products',
      'Add new product' => 'edit-field-invoice-products',
      'Add existing product' => 'edit-field-invoice-products',
    );
    $id = $mapping[$legend];
    $selector = '#' . $id . ' .fieldset-legend';
    $this->assertSession()
      ->elementTextContains('css', $selector, str_replace('\\"', '"', $legend));
  }

  /**
   * Checks that the current page contains a button with a specified label.
   *
   * @Then I should see( a) button with label :button_label
   */
  public function iShouldSeeButtonWithLabel($button_label) {
    $element = $this->getSession()->getPage();
    $button = $element->findButton($button_label);
    if (empty($button)) {
      throw new \Exception(sprintf("The button '%s' was not found on the page %s", $button_label, $this->getSession()->getCurrentUrl()));
    }
  }
}
