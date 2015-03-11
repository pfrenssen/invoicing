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
   * Checks that a fieldset with the given legend exists.
   *
   * @Then I should see( a) fieldset with( the) legend :legend
   */
  public function iShouldSeeFieldsetWithLegend($legend) {
    $this->assertSession()->elementExists('xpath', '//fieldset/legend[contains(., "' . $legend . '")]');
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
