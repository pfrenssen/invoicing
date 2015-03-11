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
   * @Then I should see the fieldset with (the )legend :legend
   */
  public function assertFieldsetWithLegend($legend) {
    $this->assertSession()->elementExists('xpath', '//fieldset/legend[contains(., "' . $legend . '")]');
  }

}
