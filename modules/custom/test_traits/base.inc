<?php

/**
 * @file
 * Asserts and helper methods to use in testing.
 */

trait BaseTestHelper {

  /**
   * Check if the properties of the given entity match the given values.
   *
   * @param string $entity_type
   *   The type of the entity.
   * @param Entity $entity
   *   The entity to check.
   * @param array $values
   *   An associative array of values to check, keyed by property name.
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertEntityProperties($entity_type, Entity $entity, array $values, $message = '', $group = 'Other') {
    $wrapper = entity_metadata_wrapper($entity_type, $entity);

    $result = TRUE;
    foreach ($values as $property => $value) {
      if (is_array($value)) {
        $result &= $this->assertFalse(array_diff($value, $wrapper->$property->value()), format_string('The %property property has the correct value.', array('%property' => $property)));
      }
      else {
        $result &= $this->assertEqual($wrapper->$property->value(), $value, format_string('The %property property has the correct value.', array('%property' => $property)));
      }
    }

    return $this->assertTrue($result, $message ?: format_string('The @entity contains the given values.', array('@entity' => $entity_type)), $group);
  }

  /**
   * Check if the given form fields are indicating that validation failed.
   *
   * This checks for the presence of the 'error' class on the field.
   *
   * @param array $fields
   *   An indexed array of field names that should be checked.
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertFieldValidationFailed(array $fields, $message = '', $group = 'Other') {
    $result = TRUE;
    foreach ($fields as $field) {
      $xpath = '//textarea[@name=:value and contains(@class, "error")]|//input[@name=:value and contains(@class, "error")]|//select[@name=:value and contains(@class, "error")]';
      $elements = $this->xpath($this->buildXPathQuery($xpath, array(':value' => $field)));
      $result &= $this->assertTrue($elements, format_string('The field %field has the "error" class.', array('%field' => $field)));
    }
    return $this->assertTrue($result, $message ?: 'All fields are indicating that validation failed.', $group);
  }

  /**
   * Check if no pager is present on the page.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertNoPager($message = '', $group = 'Other') {
    $message = $message ?: 'No pager is present on the page.';
    $xpath = '//div[@class = "item-list"]/ul[@class = "pager"]';
    return $this->assertXPathElements($xpath, 0, array(), $message, $group);
  }

  /**
   * Check if a pager is present on the page.
   *
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertPager($message = '', $group = 'Other') {
    $message = $message ?: 'A pager is present on the page.';
    $xpath = '//div[@class = "item-list"]/ul[@class = "pager"]';
    return $this->assertXPathElements($xpath, 1, array(), $message, $group);
  }

  /**
   * Check if the displayed messages match the given messages.
   *
   * This performs the following checks:
   * - All messages appear in the right place ('status', 'warning', 'error').
   * - No unexpected messages are shown.
   *
   * @param array $messages
   *   An associative array of status messages that should be displayed, keyed
   *   by message type (either 'status', 'warning' or 'error'). Every type
   *   contains an indexed array of status messages.
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertStatusMessages($messages, $message = '', $group = 'Other') {
    // Messages can contain a mix of HTML and sanitized HTML, for example:
    // '<em class="placeholder">&lt;script&gt;alert();&lt;&#039;script&gt;</em>'
    // Unfortunately, check_plain() and SimpleXML::asXml() encode quotes and
    // slashes differently. Work around this by doing the message type check
    // with decoded strings, but also check if the original encoded strings are
    // present in the raw HTML to avoid false negatives.
    $shown_messages = $this->decodeStatusMessages($this->getStatusMessages());
    $decoded_messages = $this->decodeStatusMessages($messages);

    $result = TRUE;
    foreach (array('status', 'warning', 'error') as $type) {
      $expected_messages = !empty($decoded_messages[$type]) ? $decoded_messages[$type] : array();

      // Loop over the messages that are shown and match them against the
      // expected messages.
      foreach ($shown_messages[$type] as $shown_message) {
        $key = array_search($shown_message, $expected_messages);

        // If the message is not one of the expected messages, fail.
        if ($key === FALSE) {
          $result &= $this->fail(format_string('Unexpected @type message: @message', array('@type' => $type, '@message' => $shown_message)));
        }

        // Mark found messages as passed and remove them from the list.
        else {
          $this->pass(format_string('Found @type message: @message', array('@type' => $type, '@message' => $shown_message)));
          unset($expected_messages[$key]);
        }
      }
      // Throw fails for all expected messages that are not shown.
      foreach ($expected_messages as $expected_message) {
        $result &= $this->fail(format_string('Did not find @type message: @message', array('@type' => $type, '@message' => $expected_message)));
      }
    }

    // Also check if the correctly encoded messages are present in the raw HTML.
    // The above asserts do not detect if all HTML entities are correctly
    // encoded, and could let insecure status messages slip through as false
    // negatives.
    foreach ($messages as $type => $expected_messages) {
      foreach ($expected_messages as $expected_message) {
        $result &= $this->assertRaw($expected_message, format_string('Found correctly encoded message in raw HTML: @message', array('@message' => $expected_message)));
      }
    }

    return $this->assertTrue($result, $message ?: 'The correct messages are shown.', $group);
  }

  /**
   * Check if element(s) that match the given XPath expression are present.
   *
   * @param array $xpath
   *   The XPath expression to execute on the page.
   * @param int $count
   *   The number of elements that should match the expression.
   * @param array $arguments
   *   Optional array of arguments to pass to DrupalWebTestCase::xpath().
   * @param string $message
   *   The message to display along with the assertion.
   * @param string $group
   *   The type of assertion - examples are "Browser", "PHP".
   *
   * @return bool
   *   TRUE if the assertion succeeded, FALSE otherwise.
   */
  function assertXPathElements($xpath, $count, array $arguments = array(), $message = '', $group = 'Other') {
    // Provide a default message.
    $message = $message ?: format_plural($count, 'The element matching the XPath expression is present in the page.', 'The @count elements matching the XPath expression are present in the page.');

    $elements = $this->xpath($xpath, $arguments);
    return $this->assertEqual(count($elements), $count, $message, $group);
  }

  /**
   * Decodes HTML entities of a given array of status messages.
   *
   * @param array $messages
   *   An associative array of status messages to decode, keyed by message type
   *   (either 'status', 'warning' or 'error'). Every type contains an indexed
   *   array of status messages.
   *
   * @return array
   *   The decoded array of status messages.
   */
  function decodeStatusMessages($messages) {
    foreach (array_keys($messages) as $type) {
      foreach ($messages[$type] as $key => $encoded_message) {
        $messages[$type][$key] = html_entity_decode($encoded_message, ENT_QUOTES, 'UTF-8');
      }
    }
    return $messages;
  }

  /**
   * Returns the status messages that are found in the page.
   *
   * @return array
   *   An associative array of status messages, keyed by message type (either
   *   'status', 'warning' or 'error'). Every type contains an indexed array of
   *   status messages.
   */
  function getStatusMessages() {
    $return = array(
      'error' => array(),
      'warning' => array(),
      'status' => array(),
    );

    foreach (array_keys($return) as $type) {
      // Retrieve the entire messages container.
      if ($messages = $this->xpath('//div[contains(@class, "messages") and contains(@class, :type)]', array(':type' => $type))) {
        // If only a single message is being rendered by theme_status_messages()
        // it outputs it as text preceded by an <h2> element that is provided
        // for accessibility reasons. An example:
        //
        //   <div class="messages status">
        //     <h2 class="element-invisible">Status message</h2>
        //     Email field is required.
        //   </div>
        //
        // While this is valid HTML, it is invalid XML, so this can't be parsed
        // with XPath. We can turn it into valid XML again by removing the
        // accessibility element using DOMDocument.
        $dom = new DOMDocument();

        // Load the messges HTML using UTF-8 encoding.
        @$dom->loadHTML('<html><head><meta http-equiv="Content-Type" content="text/html; charset=utf-8"/></head><body>' . $messages[0]->asXml() . '</body></html>');
        // Strip the accessibility element.
        $accessibility_message = $dom->getElementsByTagName('h2')->item(0);
        $accessibility_message->parentNode->removeChild($accessibility_message);

        // We have valid XML now, so we can use XPath to find the messages. If
        // there are multiple messages, they are output in an unordered list. A
        // single message is output directly in the <div> container.
        $xpath = new DOMXPath($dom);
        $elements = $xpath->query('//body/div/ul/li');
        if (!$elements->length) {
          $elements = $xpath->query('//body/div');
        }

        // Loop over the messages. Strip the containing element, which is either
        // a <div> or a <li>, before adding them to the return array.
        foreach ($elements as $element) {
          preg_match('/^<(li|div)[^>]*>(.*)<\/(li|div)>$/s', $dom->saveHTML($element), $matches);
          $return[$type][] = trim($matches[2]);
        }
      }
    }

    return $return;
  }

  /**
   * Returns a random address field.
   *
   * @return array
   *   A random address field.
   */
  function randomAddressField() {
    // The Address Field module trims all input and converts double spaces to
    // single spaces before saving the values to the database. We make sure our
    // random data does the same so we do not get random failures.
    // @see addressfield_field_presave()
    return array(
      'country' => chr(mt_rand(65, 90)) . chr(mt_rand(65, 90)),
      'locality' => trim(str_replace('  ', ' ', $this->randomString())),
      'postal_code' => rand(1000, 9999),
      'thoroughfare' => trim(str_replace('  ', ' ', $this->randomString())),
    );
  }

  /**
   * Returns a random email address.
   *
   * @return string
   *   A random email address.
   */
  function randomEmail() {
    return strtolower($this->randomName()) . '@example.com';
  }

  /**
   * {@inheritdoc}
   *
   * Like DrupalTestCase::randomString(), but includes additional special
   * characters, and starts with a space. This helps in discovering security
   * problems and improper trimming and encoding of strings.
   *
   * By default it returns 16 characters rather than the usual 8 to make up for
   * lost entropy.
   */
  static function randomString($length = 16) {
    $str = ' &\/;<>\'"ä☢';
    for ($i = 0; $i < $length; $i++) {
      $str .= chr(mt_rand(32, 126));
    }
    return $str;
  }

}
