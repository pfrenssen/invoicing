<?php

/**
 * @file
 * Contains \BusinessSubContext.
 */

use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;

/**
 * Behat step definitions for testing businesses.
 */
class BusinessSubContext extends DrupalSubContextBase implements DrupalSubContextInterface {

  use Drupal\invoicing\Traits\BaseTestHelper;
  use Drupal\invoicing\Traits\BusinessTestHelper;

  /**
   * Navigates to the page display of the logged in user's business.
   *
   * @When I visit my business page
   */
  public function visitBusinessPage() {
    /** @var \Business[] $businesses */
    $businesses = business_get_businesses_from_user($this->getUser());
    $business = reset($businesses);
    $this->visitPath('business/' . $business->identifier());
  }

}
