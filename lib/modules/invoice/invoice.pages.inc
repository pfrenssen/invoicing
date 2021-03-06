<?php

/**
 * @file
 * Page callbacks for adding, editing and deleting invoices.
 */

use mikehaertl\wkhtmlto\Pdf;

/**
 * Page callback: Returns the invoice add/edit form to add a new invoice.
 *
 * @param object $invoice_type
 *   The type of invoice to create.
 *
 * @return array
 *   The invoice add/edit form render array.
 *
 * @see invoice_edit_form()
 */
function invoice_add_page($invoice_type) {
  $invoice = entity_create('invoice', array('type' => $invoice_type->type));

  // If a client ID is given in the query parameters, prepopulate the client
  // field when adding an invoice.
  $parameters = drupal_get_query_parameters();
  if (!empty($parameters['cid'])) {
    // This only works if there actually is a client with the given ID.
    if ($client = client_load($parameters['cid'])) {
      // Check if the client is actually owned by the business owner.
      if (client_is_owned_by_user($client)) {
        $invoice->field_invoice_client[LANGUAGE_NONE][] = array(
          'target_id' => $client->cid,
          'revision_id' => $client->vid,
        );
      }
    }
  }

  return drupal_get_form('invoice_edit_form', $invoice);
}

/**
 * Page callback: Returns the invoice add/edit form to edit an existing invoice.
 *
 * @param Invoice $invoice
 *   The invoice to edit.
 *
 * @return array
 *   The invoice add/edit form render array.
 *
 * @see invoice_edit_form()
 */
function invoice_edit_page(Invoice $invoice) {
  drupal_set_title(t('Edit invoice'));

  return drupal_get_form('invoice_edit_form', $invoice);
}

/**
 * Form constructor for the invoice add/edit form.
 *
 * @param Invoice $invoice
 *   The invoice that is being added/edited.
 *
 * @ingroup forms
 */
function invoice_edit_form($form, &$form_state, Invoice $invoice) {
  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['invoice'])) {
    $form_state['invoice'] = $invoice;
  }
  else {
    $invoice = $form_state['invoice'];
  }

  // Attach all form elements for the fields.
  field_attach_form('invoice', $invoice, $form, $form_state, entity_language('invoice', $invoice));

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('invoice_edit_form_submit'),
  );

  if (!empty($invoice->iid) && invoice_access('delete', $invoice)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('invoice_edit_form_delete_submit'),
    );
  }

  return $form;
}

/**
 * Form validation handler for invoice_edit_form().
 */
function invoice_edit_form_validate($form, &$form_state) {
  field_attach_form_validate('invoice', $form_state['invoice'], $form, $form_state);
}

/**
 * Form submission handler for invoice_edit_form().
 *
 * Saves a invoice and outputs a status message to the user.
 */
function invoice_edit_form_submit($form, &$form_state) {
  $invoice = $form_state['invoice'];
  entity_form_submit_build_entity('invoice', $invoice, $form, $form_state);

  $operation = !empty($invoice->is_new) ? 'add' : 'edit';

  if (invoice_save($invoice)) {
    $message = $operation == 'add' ? 'New invoice has been added.' : 'The changes have been saved.';
    // @codingStandardsIgnoreStart
    drupal_set_message(t($message));
    // @codingStandardsIgnoreEnd
  }
  else {
    drupal_set_message(t('The invoice could not be saved.'), 'error');
    watchdog('invoice', 'Invoice could not be saved.', WATCHDOG_ERROR);
  }

  $form_state['redirect'] = 'invoices';
}

/**
 * Form submission handler for invoice_edit_form().
 *
 * Handles the 'Delete' button on the node form.
 *
 * @see invoice_edit_form()
 * @see invoice_delete_confirm_form()
 */
function invoice_edit_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $invoice = $form_state['invoice'];
  $form_state['redirect'] = array('invoice/' . $invoice->iid . '/delete', array('query' => $destination));
}

/**
 * Form constructor for the invoice deletion confirmation form.
 *
 * @see invoice_delete_confirm_form_submit()
 */
function invoice_delete_confirm_form($form, &$form_state, Invoice $invoice) {
  $form_state['invoice'] = $invoice;
  return confirm_form($form,
    t('Are you sure you want to delete the invoice?'),
    'invoice/' . $invoice->iid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submission handler for invoice_delete_confirm_form().
 *
 * Deletes the invoice.
 *
 * @see invoice_delete_confirm_form()
 */
function invoice_delete_confirm_form_submit($form, &$form_state) {
  $invoice = $form_state['invoice'];
  invoice_delete($invoice);
  drupal_set_message(t('The invoice has been deleted.'));
  $form_state['redirect'] = 'invoices';
}

/**
 * Page callback for the invoice page.
 */
function invoice_detail_page($invoice) {
  $output = entity_view($invoice->type, array($invoice));

  // Prevent the invoice title from being rendered twice.
  $output['invoice'][$invoice->iid]['#page'] = TRUE;

  return $output;
}

/**
 * Generates the HTML version of an invoice.
 *
 * @param Invoice $invoice
 *   The invoice to generate the HTML for.
 *
 * @return string
 *   The generated HTML.
 */
function invoice_generate_html(Invoice $invoice) {
  // Check if a valid token is present.
  if (isset($_REQUEST['token']) && invoice_get_token($invoice) == $_REQUEST['token']) {
    global $language;

    drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
    drupal_add_http_header('Content-Language', $language->language);

    $output = theme('invoice_export', array('invoice' => $invoice));
    echo $output;
    drupal_exit();
  }
  return MENU_ACCESS_DENIED;
}

/**
 * Generates the HTML version of an invoice.
 *
 * @param Invoice $invoice
 *   The invoice to generate the HTML for.
 *
 * @return string
 *   The generated HTML.
 *
 * @throws Exception
 *   Thrown when the PDF to download could not be created.
 */
function invoice_download(Invoice $invoice) {
  // Check if a valid token is present.
  if (isset($_REQUEST['token']) && drupal_valid_token($_REQUEST['token'], 'invoice-download-link-' . $invoice->identifier())) {
    $file_uri = file_build_uri('invoices/' . $invoice->iid . '.pdf');

    // Generate the PDF if it doesn't exist yet.
    if (!file_exists($file_uri)) {
      $pdf = new Pdf(array('binary' => invoicing_core_get_wkhtmltopdf_path()));
      $html = theme('invoice_export', array('invoice' => $invoice));
      $pdf->addPage($html);

      // Save the generated PDF for future reference.
      if (!$pdf->saveAs(drupal_realpath($file_uri))) {
        throw new Exception('Could not create PDF: ' . $pdf->getError());
      }
    }

    // Generate a filename in the format 'invoice-{invoice number}.pdf'.
    // @todo Add transliteration support.
    // @see https://github.com/pfrenssen/invoicing/issues/37
    $invoice_wrapped = entity_metadata_wrapper('invoice', $invoice);
    $invoice_number = $invoice_wrapped->field_invoice_number->value();
    $filename = t('invoice-@invoice-number.pdf', array('@invoice-number' => $invoice_number));

    // Send the PDF to the browser as a file download.
    $headers = array(
      'Cache-Control' => 'private',
      'Content-Type' => 'application/pdf',
      'Content-Disposition' => 'attachment; filename="' . $filename . '"',
    );

    file_transfer($file_uri, $headers);
  }
  return MENU_ACCESS_DENIED;
}
