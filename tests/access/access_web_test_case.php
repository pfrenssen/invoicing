<?php

/**
 * @file
 * Contains \AccessWebTestCase.
 */

/**
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
   *   An array of paths. These may be either strings, or an array with the
   *   following keys:
   *   - path: Drupal path or external URL to load into internal browser.
   *   - options: Options to be forwarded to url().
   */
  protected $accessiblePaths = array();

  /**
   * A list of paths that should be inaccessible.
   *
   * @var array
   *   An array of paths. These may be either strings, or an array with the
   *   following keys:
   *   - path: Drupal path or external URL to load into internal browser.
   *   - options: Options to be forwarded to url().
   */
  protected $inaccessiblePaths = array();

  /**
   * A list of paths that should not exist.
   *
   * @var array
   *   An array of paths. These may be either strings, or an array with the
   *   following keys:
   *   - path: Drupal path or external URL to load into internal browser.
   *   - options: Options to be forwarded to url().
   */
  protected $nonExistingPaths = array(
    'line_item/add',
    'line_item/add/product',
    'line_item/add/service',
  );

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
    $this->doInaccessiblePathsTest();
    $this->doNonExistingPathsTest();
  }

  /**
   * Checks if the defined paths are accessible.
   */
  protected function doAccessiblePathsTest() {
    foreach ($this->accessiblePaths as $path) {
      $url_arguments = $this->convertPathToUrlArguments($path);
      $this->drupalGet($url_arguments['path'], $url_arguments['options']);
      $this->assertResponse('200', format_string('The path %path is accessible.', array('%path' => $url_arguments['path'])));
    }
  }

  /**
   * Checks if the defined paths are inaccessible.
   */
  protected function doInaccessiblePathsTest() {
    foreach ($this->inaccessiblePaths as $path) {
      $url_arguments = $this->convertPathToUrlArguments($path);
      $this->drupalGet($url_arguments['path'], $url_arguments['options']);
      $this->assertResponse('403', format_string('The path %path is inaccessible.', array('%path' => $url_arguments['path'])));
    }
  }

  /**
   * Checks if the defined paths return page not found errors.
   */
  protected function doNonExistingPathsTest() {
    foreach ($this->nonExistingPaths as $path) {
      $url_arguments = $this->convertPathToUrlArguments($path);
      $this->drupalGet($url_arguments['path'], $url_arguments['options']);
      $this->assertResponse('404', format_string('The path %path does not exist.', array('%path' => $url_arguments['path'])));
    }
  }

  /**
   * Converts the path into arguments for the url() function.
   *
   * @param string|array $path
   *   Either a string representing an internal path or an external url, or an
   *   array with the following keys:
   *   - path: Drupal path or external URL to load into internal browser.
   *   - options: Options to be forwarded to url().
   *
   * @return array
   *   An array with the following keys:
   *   - path: Drupal path or external URL to load into internal browser.
   *   - options: Options to be forwarded to url().
   */
  protected function convertPathToUrlArguments($path) {
    if (!is_array($path)) {
      $path = array('path' => $path, 'options' => array());
    }

    return $path;
  }

}
