<?php

namespace Drupal\invoicing\Context;

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Drupal\DrupalExtension\Hook\Scope\AfterUserCreateScope;
use Drupal\invoicing\Traits\BaseTestHelper;
use Drupal\invoicing\Traits\BusinessTestHelper;

/**
 * Generic methods and step definitions for the Invoicing platform.
 */
class InvoicingContext extends RawDrupalContext {

  use BaseTestHelper;
  use BusinessTestHelper;

  /**
   * When a business owner is created, create a business for it.
   *
   * @param AfterUserCreateScope $scope
   *   The user scope object.
   *
   * @afterUserCreate
   */
  public function createBusinessForBusinessOwner(AfterUserCreateScope $scope) {
    $entity = $scope->getEntity();
    if ($entity->role === 'business owner') {
      $user = user_load($entity->uid);
      $business = $this->createBusiness();
      $business->save();
      $this->addBusinessToUser($business, $user);
    }
  }

}
