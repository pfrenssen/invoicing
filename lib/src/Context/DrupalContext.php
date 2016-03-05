<?php

namespace Drupal\invoicing\Context;

use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;

/**
 * Provides pre-built step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {

  /**
   * {@inheritdoc}
   */
  public function loggedIn() {
    // This is different from the parent class in that it checks if the user is
    // logged in by the presence of a CSS class on the body element, rather than
    // having a log out link present on the page.
    $session = $this->getSession();
    $session->visit($this->locatePath('/'));

    // Check if the 'user-logged-in' class is present on the page.
    $element = $session->getPage();
    return $element->find('css', 'body.logged-in');
  }

}
