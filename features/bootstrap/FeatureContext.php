<?php

/**
 * @file
 * Contains \FeatureContext.
 */

use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\TableNode;
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

  /**
   * Presses the given button in the given fieldset.
   *
   * @param string $button
   *   The id|name|title|alt|value of the button to be pressed.
   * @param string $fieldset_id
   *   The ID or legend text of the fieldset in which the button should be
   *   pressed.
   *
   * @throws \Exception
   *   Thrown if the fieldset or the button within it cannot be found.
   *
   * @When I press :button in the :fieldset fieldset
   */
  public function assertButtonPressedInFieldset($button, $fieldset_id) {
    $page = $this->getSession()->getPage();
    $fieldset = $page->find('named', array('fieldset', $this->getSession()->getSelectorsHandler()->xpathLiteral($fieldset_id)));
    if (empty($fieldset)) {
      throw new \Exception(sprintf("The fieldset '%s' was not found on the page '%s'.", $button, $this->getSession()->getCurrentUrl()));
    }
    $fieldset->pressButton($button);
  }

  /**
   * Enters the data given in the table in form fields.
   *
   * @param \Behat\Gherkin\Node\TableNode $data
   *   The data to enter in the fields, keyed by field ID, name or label.
   *
   * @Given I enter the following:
   */
  public function assertEnterField(TableNode $data) {
    $page = $this->getSession()->getPage();
    foreach ($data->getRowsHash() as $field => $value) {
      $page->fillField($field, $value);
    }
  }

  /**
   * Verifies that the data given in the table exists in form fields.
   *
   * @param \Behat\Gherkin\Node\TableNode $data
   *   The data that should be present in the fields, keyed by field ID, name or
   *   label.
   *
   * @Then I should see the following field values:
   */
  public function assertFieldsContain(TableNode $data) {
    foreach ($data->getRowsHash() as $field => $value) {
      $this->assertSession()->fieldValueEquals($field, $value);
    }
  }

  /**
   * Verifies that the given option is selected for a set of radio buttons.
   *
   * @param string $label
   *   The label of the option that should be selected.
   *
   * @throws \Exception
   *   Thrown when a radio button with the given option was not found, or when
   *   it was not selected.
   *
   * @Then the radio button (option ):label should be selected
   */
  public function assertRadioButtonIsSelected($label) {
    $page = $this->getSession()->getPage();
    $radiobutton = $page->find('named', array('radio', $this->getSession()->getSelectorsHandler()->xpathLiteral($label)));

    if ($radiobutton === NULL) {
      throw new \Exception(sprintf('The radio button with "%s" was not found on the page %s', $label, $this->getSession()->getCurrentUrl()));
    }
    if ($radiobutton->getValue() !== $label) {
      throw new \Exception(sprintf('The radio button with "%s" was not selected.', $label, $this->getSession()->getCurrentUrl()));
    }
  }

}
