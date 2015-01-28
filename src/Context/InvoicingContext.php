<?php

/**
 * @file
 * Contains \Drupal\invoicing\Context\InvoicingContext.
 */

namespace Drupal\invoicing\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Drupal\DrupalExtension\Hook\Scope\AfterUserCreateScope;

require_once('modules/custom/test_traits/base.inc');
require_once('modules/custom/test_traits/business.inc');

/**
 * Generic methods and step definitions for the Invoicing platform.
 */
class InvoicingContext extends RawDrupalContext {
  use \BaseTestHelper;
  use \BusinessTestHelper;

  /**
   * When a business owner is created, create a business for it.
   *
   * @param AfterUserCreateScope $scope
   *   The user scope object.
   *
   * @afterUserCreate
   */
  public function createBusinessForBusinessOwner(AfterUserCreateScope $scope) {
    $user = user_load($scope->getEntity()->uid);
    $business = $this->createBusiness();
    $business->save();
    $this->addBusinessToUser($business, $user);
  }

}
