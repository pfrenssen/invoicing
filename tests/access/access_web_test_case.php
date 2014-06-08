<?php

/**
 * @file
 * Base class for access and permission tests.
 */
abstract class AccessWebTestCase extends InvoicingIntegrationTestCase {

  /**
   * The user account that is being tested.
   *
   * @var object
   */
  protected $user;

  /**
   * The user role that is being tested.
   *
   * @var string
   */
  protected $role;

  /**
   * A list of paths that should be accessible.
   *
   * @var array
   */
  protected $accessiblePaths = array();

  /**
   * A list of paths that should be inaccessible.
   *
   * @var array
   */
  protected $inaccessiblePaths = array();

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();

    $this->setupUser();
  }

  /**
   * Creates and logs in the test user.
   */
  protected function setupUser() {
    // Check that a user role has been defined by the subclass.
    $this->assertTrue($this->role, 'A user role has been defined.');

    // Log in the user.
    $this->drupalLogin($this->users[$this->role]);
  }

  /**
   * Tests access for a user role.
   */
  public function testAccess() {
    $this->doAccessiblePathsTest();
    $this->doInAccessiblePathsTest();
  }

  /**
   * Checks if the defined paths are accessible.
   */
  protected function doAccessiblePathsTest() {
    foreach ($this->accessiblePaths as $path) {
      $this->drupalGet($path);
      $this->assertResponse('200', format_string('The path %path is accessible.', array('%path' => $path)));
    }
  }

  /**
   * Checks if the defined paths are inaccessible.
   */
  protected function doInAccessiblePathsTest() {
    foreach ($this->inaccessiblePaths as $path) {
      $this->drupalGet($path);
      $this->assertResponse('403', format_string('The path %path is inaccessible.', array('%path' => $path)));
    }
  }

}
