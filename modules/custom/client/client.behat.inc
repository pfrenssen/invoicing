<?php

/**
 * @file
 * Contains \ClientSubContext.
 */

use Behat\Gherkin\Node\TableNode;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\DrupalSubContextInterface;

/**
 * Behat step definitions for testing clients.
 */
class ClientSubContext extends DrupalSubContextBase implements DrupalSubContextInterface {

  use Drupal\invoicing\Traits\BaseTestHelper;
  use Drupal\invoicing\Traits\ClientTestHelper;

  /**
   * Test clients.
   *
   * @var Client[]
   */
  public $clients = array();

  /**
   * Creates clients with data provided in a table.
   *
   * Table format:
   * | name    | email           |
   * | Axemill | info@axemill.eu |
   *
   * @param TableNode $clients_table
   *   The client data.
   *
   * @throws \Exception
   *   Thrown when no user is logged in.
   *
   * @Given client(s):
   */
  public function createClients(TableNode $clients_table) {
    if (!$this->getuser()->uid) {
      throw new \Exception('There is no current logged in user to create clients for.');
    }

    $user = entity_metadata_wrapper('user', user_load($this->getUser()->uid));
    $businesses = $user->field_user_businesses->value();

    if (empty($businesses)) {
      throw new \Exception('Cannot create clients, the currently logged in user has no business.');
    }

    foreach ($clients_table->getHash() as $client_hash) {
      $client = $this->createClient(array(
        'bid' => $businesses[0]->identifier(),
        'name' => $client_hash['name'],
        'field_client_email' => $client_hash['email'],
      ));
      client_save($client);
      $this->clients[$client_hash['name']] = $client;
    }
  }

  /**
   * Checks the number of clients that the currently logged in user has.
   *
   * @param int $count
   *   The number of clients the logged in user is supposed to have.
   *
   * @throws \Exception
   *   Thrown when the user is not logged in.
   *
   * @Then I should have :count client(s)
   */
  public function assertClientCount($count) {
    if (!$this->getUser()->uid) {
      throw new \Exception('The user is not logged in.');
    }

    $user = user_load($this->getUser()->uid);
    $cids = client_get_client_ids_from_user($user, TRUE);
    PHPUnit_Framework_Assert::assertEquals($count, count($cids));
  }

  /**
   * Remove any created clients.
   *
   * @AfterScenario
   */
  public function cleanClients() {
    // Remove any clients that were created.
    foreach ($this->clients as $client) {
      client_delete($client);
    }
  }

}
