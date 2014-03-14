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
  function construct() {
    parent::construct();

    // Make sure the client id is available in the query.
    $this->additional_fields['cid'] = 'cid';
  }

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    // Provide an option to override the link text.
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
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
  function query() {
    // Make sure the table and additional fields are added to the query.
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    // Default to 'view' if no link text is specified.
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');

    // Return a link to the client.
    $cid = $values->{$this->aliases['cid']};
    return l($text, 'client/' . $cid);
  }

}
