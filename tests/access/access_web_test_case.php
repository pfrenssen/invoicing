<?php

/**
 * @file
 * Base class for access and permission tests.
 */
class AccessWebTestCase extends DrupalWebTestCase {

  /**
   * {@inheritdoc}
   */
  protected $profile = 'invoicing';

  /**
   * Tests access for a user role.
   */
  public function testAccess() {
  }

}
