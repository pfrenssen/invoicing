<?php

/**
 * @file
 * Contains client_handler_link_field.
 */

/**
 * Field handler to present a simple link to a client.
 */
class client_handler_link_field extends views_handler_field {

  /**
   * Constructs a client_handler_link_field object.
   */
  public function construct() {
    parent::construct();

    // Make sure the client id and type are available in the query.
    $this->additional_fields['cid'] = 'cid';
    $this->additional_fields['type'] = 'type';
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    // Provide an option to override the link text.
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    // The form field to set the link text.
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    // Make sure the table and additional fields are added to the query.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    // Default to 'view' if no link text is specified.
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');

    // Return a link to the client.
    $client = client_create(array(
      'cid' => $values->{$this->aliases['cid']},
      'type' => $values->{$this->aliases['type']},
    ));
    return $this->render_link($client, $values);
  }

  /**
   * Renders the link.
   *
   * @param Client $client
   *   The client for which to render the link.
   * @param \stdClass $values
   *   The values retrieved from the database.
   *
   * @return string
   *   The rendered link.
   */
  public function render_link(Client $client, \stdClass $values) {
    if (client_access('view', $client)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "client/$client->cid";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
      return $text;
    }
  }

}
