<?php

/**
 * @file
 * Contains client_handler_delete_link_field.
 */

/**
 * Field handler to present a link to delete a tax rate.
 */
class tax_rate_handler_delete_link_field extends views_handler_field {
  /**
   * Constructs a client_handler_link_field object.
   */
  public function construct() {
    parent::construct();

    // Make sure the tax rate id is available in the query.
    $this->additional_fields['tid'] = 'tid';
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
    $tax_rate = line_item_tax_rate_load($values->{$this->aliases['tid']});

    return $this->render_link($tax_rate, $values);
  }

  /**
   * {@inheritdoc}
   */
  public function render_link($tax_rate, $values) {
    if (line_item_tax_rate_access('delete', $tax_rate)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "settings/tax-rates/$tax_rate->tid/delete";
      $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
      return $text;
    }
  }

}
