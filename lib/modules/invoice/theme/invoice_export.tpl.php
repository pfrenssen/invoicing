<?php

/**
 * @file
 * Default template for invoices.
 *
 * The following invoice related variables are available:
 * - $invoice_date: The invoice date.
 * - $invoice_discount: The discount applied to the invoice.
 * - $invoice_due_date: The due date.
 * - $invoice_number: The invoice number.
 * - $invoice_po_number: The purchase order number.
 * - $invoice_products: The table of products.
 * - $invoice_services: The table of services.
 * - $invoice_terms: The terms and conditions.
 *
 * Variables concerning the business that is issuing the invoice:
 * - $business_name: The business name. This is a sanitized string.
 * - $business_address: The postal address.
 * - $business_bic: The BIC number.
 * - $business_email: The e-mail address.
 * - $business_iban: The IBAN number.
 * - $business_mobile: The mobile phone number.
 * - $business_phone: The phone number.
 * - $business_vat: The VAT number.
 *
 * Variables concerning the client to which the invoice is addressed:
 * - $client_name: The client name, this is a sanitized string.
 * - $client_address: The postal address of the head office.
 * - $client_email: The e-mail address.
 * - $client_phone: The phone number.
 * - $client_shipping_address: The postal address of the warehouse.
 * - $client_vat: The VAT number.
 * - $client_website: The website.
 *
 * Variables concerning the line items:
 * - $products: A rendered HTML table containing the products.
 * - $services: A rendered HTML table containing the services.
 */
global $language;
$name = $language->language == 'bg' ? 'Питър Френсън' : 'Pieter Frenssen';
?>
<html>
  <head>
    <meta charset="utf-8">
    <style type="text/css" media="all">@import url("http://invoicing.local/profiles/invoicing/modules/custom/invoice/theme/invoice_export.css");</style>
    <?php print $styles; ?>
  </head>
  <body>
    <div id="invoice">
      <h1><?php print t('Invoice'); ?></h1>
      <div id="invoice-originality"><?php print t('Original'); ?></div>
      <div id="invoice-details-left">
        <?php if ($invoice_number): ?>
          <div id="invoice-number"><?php print render($invoice_number); ?></div>
        <?php endif; ?>
        <div class="field-label"><?php print t('Place of issue'); ?>:</div>
        <div id="invoice-place"><?php print t('Sofia'); ?></div>
      </div>
      <div id="invoice-details-right">
        <?php if ($invoice_date): ?>
          <div id="invoice-date"><?php print render($invoice_date); ?></div>
        <?php endif; ?>
        <div class="field-label"><?php print t('Date of tax event'); ?>:</div>
        <div id="invoice-tax-date"><?php print $invoice_date[0]['#markup']; ?></div>
      </div>
    </div>
    <div id="company-details">
      <div id="first-column">
        <div id="client">
          <h2><?php print t('Recipient'); ?></h2>
          <?php if ($client_name): ?>
            <div class="field-label"><?php print t('Company name'); ?>:</div>
            <div id="client-name"><?php print $client_name; ?></div>
          <?php endif; ?>
          <?php if ($client_address): ?>
            <div id="client-address"><?php print render($client_address); ?></div>
          <?php endif; ?>
          <div id="client-contact">
            <?php if ($client_email): ?>
              <div id="client-email"><?php print render($client_email); ?></div>
            <?php endif; ?>
            <?php if ($client_phone): ?>
              <div id="client-phone"><?php print render($client_phone); ?></div>
            <?php endif; ?>
          </div>
          <?php if ($client_number): ?>
            <div id="client-number"><?php print render($client_number); ?></div>
          <?php endif; ?>
          <?php if($client_vat): ?>
            <div id="client-vat"><?php print render($client_vat); ?></div>
          <?php endif; ?>
          <?php if ($client_accountable): ?>
            <div id="client-accountable"><?php print render($client_accountable); ?></div>
          <?php endif; ?>
        </div>
      </div>
      <div id="second-column">
        <div id="business">
          <h2><?php print t('Supplier'); ?></h2>
          <?php if ($business_name): ?>
          <!-- @todo Change field label from Business name to Company name.
            <div class="field-label"><?php print t('Company name'); ?>:</div>
           -->
            <div id="business-name"><?php print render($business_name); ?></div>
          <?php endif; ?>
          <?php if ($business_address): ?>
            <div id="business-address"><?php print render($business_address); ?></div>
          <?php endif; ?>
          <div id="business-contact">
            <?php if ($business_email): ?>
              <div id="business-email"><?php print render($business_email); ?></div>
            <?php endif; ?>
            <?php if($business_phone): ?>
              <div id="business-phone"><?php print render($business_phone); ?></div>
            <?php endif; ?>
            <?php if($business_mobile): ?>
              <div id="business-mobile"><?php print render($business_mobile); ?></div>
            <?php endif; ?>
          </div>
          <div class="field-label"><?php print t('Company number'); ?>:</div>
          <div id="business-number">203805153</div>
          <?php if($business_vat): ?>
            <div id="business-vat"><?php print render($business_vat); ?></div>
          <?php endif; ?>
          <div class="field-label"><?php print t('Accountable'); ?>:</div>
          <div id="business-accountable"><?php print $name; ?></div>
        </div>
      </div>
    </div>
    <div id="tables">
      <?php if ($products): ?>
        <div id="products"><?php print $products; ?></div>
      <?php endif; ?>
      <?php if ($services): ?>
        <div id="services"><?php print $services; ?></div>
      <?php endif; ?>
      <?php print $totals; ?>
    </div>
    <div id="payment-details">
      <div class="field-label"><?php print t('In words'); ?>:</div>
      <div id="invoice-total-words"><?php print $invoice_total_words; ?></div>
      <div class="field-label"><?php print t('Payment method'); ?>:</div>
      <div id="invoice-payment-method"><?php print t('Bank transfer'); ?></div>
      <div class="field-label"><?php print t('Bank'); ?>:</div>
      <div id="business-bank"><?php print t('Raiffeisen Bank'); ?></div>
      <?php if($business_iban): ?>
        <div id="business-iban"><?php print render($business_iban); ?></div>
      <?php endif; ?>
      <?php if ($business_bic): ?>
        <div id="business-bic"><?php print render($business_bic); ?></div>
      <?php endif; ?>
      <?php if ($invoice_due_date): ?>
        <div id="invoice-due-date"><?php print render($invoice_due_date); ?></div>
      <?php endif; ?>
    </div>

    <div id="terms">
      <?php print t('The delivery is not subject to VAT taxation in Bulgaria in accordance with the VAT reverse charge system, art. 21, paragraph 2 of the VAT act.'); ?>
    </div>
    <?php if ($invoice_terms): ?>
      <div id="terms">
        <?php print render($invoice_terms); ?>
      </div>
    <?php endif; ?>

    <div id="signature">
      <div class="field-label"><?php print t('Prepared by'); ?>:</div>
      <div id="invoice-issuer"><?php print $name; ?></div>
      <div class="field-label"><?php print t('Signature'); ?>:</div>
    </div>
  </body>
</html>
