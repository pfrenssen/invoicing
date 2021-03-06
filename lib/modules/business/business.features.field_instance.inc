<?php
/**
 * @file
 * business.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function business_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'business-business-field_business_address'.
  $field_instances['business-business-field_business_address'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'addressfield',
        'settings' => array(
          'format_handlers' => array(
            0 => 'address',
          ),
          'use_widget_handlers' => 1,
        ),
        'type' => 'addressfield_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_address',
    'label' => 'Invoice address',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'addressfield',
      'settings' => array(
        'available_countries' => array(),
        'default_country' => '',
        'format_handlers' => array(
          'address' => 'address',
          'address-optional' => 'address-optional',
          'address-hide-postal-code' => 0,
          'address-hide-street' => 0,
          'address-hide-country' => 0,
          'organisation' => 0,
          'name-full' => 0,
          'name-oneline' => 0,
        ),
      ),
      'type' => 'addressfield_standard',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'business-business-field_business_bic'.
  $field_instances['business-business-field_business_bic'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_bic',
    'label' => 'BIC number',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'business-business-field_business_email'.
  $field_instances['business-business-field_business_email'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'email',
        'settings' => array(),
        'type' => 'email_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_email',
    'label' => 'Email address',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'email',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'email_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'business-business-field_business_iban'.
  $field_instances['business-business-field_business_iban'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_iban',
    'label' => 'IBAN number',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'business-business-field_business_mobile'.
  $field_instances['business-business-field_business_mobile'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'phone',
        'settings' => array(
          'allow_alpha' => FALSE,
          'as_tel_link' => FALSE,
          'components' => array(
            'extension' => 'extension',
            'numbertype' => 'numbertype',
          ),
          'country_name_position' => 'after',
          'extension_prefix' => ' ext. ',
          'full_hcard' => FALSE,
          'numbertype_position' => 'before',
        ),
        'type' => 'phone_international',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_mobile',
    'label' => 'Mobile number',
    'required' => 0,
    'settings' => array(
      'country_options' => array(
        'all_country_codes' => 1,
        'country_codes' => array(
          'country_selection' => array(
            'AC' => 0,
            'AD' => 0,
            'AE' => 0,
            'AF' => 'AF',
            'AG' => 0,
            'AI' => 0,
            'AL' => 0,
            'AM' => 0,
            'AO' => 0,
            'AR' => 0,
            'AS' => 0,
            'AT' => 0,
            'AU' => 0,
            'AW' => 0,
            'AX' => 0,
            'AZ' => 0,
            'BA' => 0,
            'BB' => 0,
            'BD' => 0,
            'BE' => 'BE',
            'BF' => 0,
            'BG' => 0,
            'BH' => 0,
            'BI' => 0,
            'BJ' => 0,
            'BL' => 0,
            'BM' => 0,
            'BN' => 0,
            'BO' => 0,
            'BQ' => 0,
            'BR' => 0,
            'BS' => 0,
            'BT' => 0,
            'BW' => 0,
            'BY' => 0,
            'BZ' => 0,
            'CA' => 0,
            'CC' => 0,
            'CD' => 0,
            'CF' => 0,
            'CG' => 0,
            'CH' => 0,
            'CI' => 0,
            'CK' => 0,
            'CL' => 0,
            'CM' => 0,
            'CN' => 0,
            'CO' => 0,
            'CR' => 0,
            'CU' => 0,
            'CV' => 0,
            'CW' => 0,
            'CX' => 0,
            'CY' => 0,
            'CZ' => 0,
            'DE' => 0,
            'DJ' => 0,
            'DK' => 0,
            'DM' => 0,
            'DO' => 0,
            'DZ' => 0,
            'EC' => 0,
            'EE' => 0,
            'EG' => 0,
            'EH' => 0,
            'ER' => 0,
            'ES' => 0,
            'ET' => 0,
            'FI' => 0,
            'FJ' => 0,
            'FK' => 0,
            'FM' => 0,
            'FO' => 0,
            'FR' => 0,
            'GA' => 0,
            'GB' => 0,
            'GD' => 0,
            'GE' => 0,
            'GF' => 0,
            'GG' => 0,
            'GH' => 0,
            'GI' => 0,
            'GL' => 0,
            'GM' => 0,
            'GN' => 0,
            'GP' => 0,
            'GQ' => 0,
            'GR' => 0,
            'GT' => 0,
            'GU' => 0,
            'GW' => 0,
            'GY' => 0,
            'HK' => 0,
            'HN' => 0,
            'HR' => 0,
            'HT' => 0,
            'HU' => 0,
            'ID' => 0,
            'IE' => 0,
            'IL' => 0,
            'IM' => 0,
            'IN' => 0,
            'IO' => 0,
            'IQ' => 0,
            'IR' => 0,
            'IS' => 0,
            'IT' => 0,
            'JE' => 0,
            'JM' => 0,
            'JO' => 0,
            'JP' => 0,
            'KE' => 0,
            'KG' => 0,
            'KH' => 0,
            'KI' => 0,
            'KM' => 0,
            'KN' => 0,
            'KP' => 0,
            'KR' => 0,
            'KW' => 0,
            'KY' => 0,
            'KZ' => 0,
            'LA' => 0,
            'LB' => 0,
            'LC' => 0,
            'LI' => 0,
            'LK' => 0,
            'LR' => 0,
            'LS' => 0,
            'LT' => 0,
            'LU' => 0,
            'LV' => 0,
            'LY' => 0,
            'MA' => 0,
            'MC' => 0,
            'MD' => 0,
            'ME' => 0,
            'MF' => 0,
            'MG' => 0,
            'MH' => 0,
            'MK' => 0,
            'ML' => 0,
            'MM' => 0,
            'MN' => 0,
            'MO' => 0,
            'MP' => 0,
            'MQ' => 0,
            'MR' => 0,
            'MS' => 0,
            'MT' => 0,
            'MU' => 0,
            'MV' => 0,
            'MW' => 0,
            'MX' => 0,
            'MY' => 0,
            'MZ' => 0,
            'NA' => 0,
            'NC' => 0,
            'NE' => 0,
            'NF' => 0,
            'NG' => 0,
            'NI' => 0,
            'NL' => 0,
            'NO' => 0,
            'NP' => 0,
            'NR' => 0,
            'NU' => 0,
            'NZ' => 0,
            'OM' => 0,
            'PA' => 0,
            'PE' => 0,
            'PF' => 0,
            'PG' => 0,
            'PH' => 0,
            'PK' => 0,
            'PL' => 0,
            'PM' => 0,
            'PR' => 0,
            'PS' => 0,
            'PT' => 0,
            'PW' => 0,
            'PY' => 0,
            'QA' => 0,
            'RE' => 0,
            'RO' => 0,
            'RS' => 0,
            'RU' => 0,
            'RW' => 0,
            'SA' => 0,
            'SB' => 0,
            'SC' => 0,
            'SD' => 0,
            'SE' => 0,
            'SG' => 0,
            'SH' => 0,
            'SI' => 0,
            'SJ' => 0,
            'SK' => 0,
            'SL' => 0,
            'SM' => 0,
            'SN' => 0,
            'SO' => 0,
            'SR' => 0,
            'SS' => 0,
            'ST' => 0,
            'SV' => 0,
            'SX' => 0,
            'SY' => 0,
            'SZ' => 0,
            'TC' => 0,
            'TD' => 0,
            'TG' => 0,
            'TH' => 0,
            'TJ' => 0,
            'TK' => 0,
            'TL' => 0,
            'TM' => 0,
            'TN' => 0,
            'TO' => 0,
            'TR' => 0,
            'TT' => 0,
            'TV' => 0,
            'TW' => 0,
            'TZ' => 0,
            'UA' => 0,
            'UG' => 0,
            'US' => 0,
            'UY' => 0,
            'UZ' => 0,
            'VA' => 0,
            'VC' => 0,
            'VE' => 0,
            'VG' => 0,
            'VI' => 0,
            'VN' => 0,
            'VU' => 0,
            'WF' => 0,
            'WS' => 0,
            'YE' => 0,
            'YT' => 0,
            'ZA' => 0,
            'ZM' => 0,
            'ZW' => 0,
          ),
          'hide_single_cc' => 0,
        ),
        'default_country' => 'BE',
        'enable_country' => 1,
        'enable_default_country' => 1,
      ),
      'enable_extension' => 0,
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'phone',
      'settings' => array(
        'country_code_position' => 'after',
        'extension_size' => 7,
        'label_position' => 'none',
        'number_size' => 30,
        'numbertype_allowed_values_position' => 'before',
        'use_tel_input' => 1,
      ),
      'type' => 'phone',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'business-business-field_business_name'.
  $field_instances['business-business-field_business_name'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_name',
    'label' => 'Business name',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'business-business-field_business_phone'.
  $field_instances['business-business-field_business_phone'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'phone',
        'settings' => array(
          'allow_alpha' => FALSE,
          'as_tel_link' => FALSE,
          'components' => array(
            'extension' => 'extension',
            'numbertype' => 'numbertype',
          ),
          'country_name_position' => 'after',
          'extension_prefix' => ' ext. ',
          'full_hcard' => FALSE,
          'numbertype_position' => 'before',
        ),
        'type' => 'phone_international',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_phone',
    'label' => 'Phone number',
    'required' => 0,
    'settings' => array(
      'country_options' => array(
        'all_country_codes' => 1,
        'country_codes' => array(
          'country_selection' => array(
            'AC' => 0,
            'AD' => 0,
            'AE' => 0,
            'AF' => 'AF',
            'AG' => 0,
            'AI' => 0,
            'AL' => 0,
            'AM' => 0,
            'AO' => 0,
            'AR' => 0,
            'AS' => 0,
            'AT' => 0,
            'AU' => 0,
            'AW' => 0,
            'AX' => 0,
            'AZ' => 0,
            'BA' => 0,
            'BB' => 0,
            'BD' => 0,
            'BE' => 'BE',
            'BF' => 0,
            'BG' => 0,
            'BH' => 0,
            'BI' => 0,
            'BJ' => 0,
            'BL' => 0,
            'BM' => 0,
            'BN' => 0,
            'BO' => 0,
            'BQ' => 0,
            'BR' => 0,
            'BS' => 0,
            'BT' => 0,
            'BW' => 0,
            'BY' => 0,
            'BZ' => 0,
            'CA' => 0,
            'CC' => 0,
            'CD' => 0,
            'CF' => 0,
            'CG' => 0,
            'CH' => 0,
            'CI' => 0,
            'CK' => 0,
            'CL' => 0,
            'CM' => 0,
            'CN' => 0,
            'CO' => 0,
            'CR' => 0,
            'CU' => 0,
            'CV' => 0,
            'CW' => 0,
            'CX' => 0,
            'CY' => 0,
            'CZ' => 0,
            'DE' => 0,
            'DJ' => 0,
            'DK' => 0,
            'DM' => 0,
            'DO' => 0,
            'DZ' => 0,
            'EC' => 0,
            'EE' => 0,
            'EG' => 0,
            'EH' => 0,
            'ER' => 0,
            'ES' => 0,
            'ET' => 0,
            'FI' => 0,
            'FJ' => 0,
            'FK' => 0,
            'FM' => 0,
            'FO' => 0,
            'FR' => 0,
            'GA' => 0,
            'GB' => 0,
            'GD' => 0,
            'GE' => 0,
            'GF' => 0,
            'GG' => 0,
            'GH' => 0,
            'GI' => 0,
            'GL' => 0,
            'GM' => 0,
            'GN' => 0,
            'GP' => 0,
            'GQ' => 0,
            'GR' => 0,
            'GT' => 0,
            'GU' => 0,
            'GW' => 0,
            'GY' => 0,
            'HK' => 0,
            'HN' => 0,
            'HR' => 0,
            'HT' => 0,
            'HU' => 0,
            'ID' => 0,
            'IE' => 0,
            'IL' => 0,
            'IM' => 0,
            'IN' => 0,
            'IO' => 0,
            'IQ' => 0,
            'IR' => 0,
            'IS' => 0,
            'IT' => 0,
            'JE' => 0,
            'JM' => 0,
            'JO' => 0,
            'JP' => 0,
            'KE' => 0,
            'KG' => 0,
            'KH' => 0,
            'KI' => 0,
            'KM' => 0,
            'KN' => 0,
            'KP' => 0,
            'KR' => 0,
            'KW' => 0,
            'KY' => 0,
            'KZ' => 0,
            'LA' => 0,
            'LB' => 0,
            'LC' => 0,
            'LI' => 0,
            'LK' => 0,
            'LR' => 0,
            'LS' => 0,
            'LT' => 0,
            'LU' => 0,
            'LV' => 0,
            'LY' => 0,
            'MA' => 0,
            'MC' => 0,
            'MD' => 0,
            'ME' => 0,
            'MF' => 0,
            'MG' => 0,
            'MH' => 0,
            'MK' => 0,
            'ML' => 0,
            'MM' => 0,
            'MN' => 0,
            'MO' => 0,
            'MP' => 0,
            'MQ' => 0,
            'MR' => 0,
            'MS' => 0,
            'MT' => 0,
            'MU' => 0,
            'MV' => 0,
            'MW' => 0,
            'MX' => 0,
            'MY' => 0,
            'MZ' => 0,
            'NA' => 0,
            'NC' => 0,
            'NE' => 0,
            'NF' => 0,
            'NG' => 0,
            'NI' => 0,
            'NL' => 0,
            'NO' => 0,
            'NP' => 0,
            'NR' => 0,
            'NU' => 0,
            'NZ' => 0,
            'OM' => 0,
            'PA' => 0,
            'PE' => 0,
            'PF' => 0,
            'PG' => 0,
            'PH' => 0,
            'PK' => 0,
            'PL' => 0,
            'PM' => 0,
            'PR' => 0,
            'PS' => 0,
            'PT' => 0,
            'PW' => 0,
            'PY' => 0,
            'QA' => 0,
            'RE' => 0,
            'RO' => 0,
            'RS' => 0,
            'RU' => 0,
            'RW' => 0,
            'SA' => 0,
            'SB' => 0,
            'SC' => 0,
            'SD' => 0,
            'SE' => 0,
            'SG' => 0,
            'SH' => 0,
            'SI' => 0,
            'SJ' => 0,
            'SK' => 0,
            'SL' => 0,
            'SM' => 0,
            'SN' => 0,
            'SO' => 0,
            'SR' => 0,
            'SS' => 0,
            'ST' => 0,
            'SV' => 0,
            'SX' => 0,
            'SY' => 0,
            'SZ' => 0,
            'TC' => 0,
            'TD' => 0,
            'TG' => 0,
            'TH' => 0,
            'TJ' => 0,
            'TK' => 0,
            'TL' => 0,
            'TM' => 0,
            'TN' => 0,
            'TO' => 0,
            'TR' => 0,
            'TT' => 0,
            'TV' => 0,
            'TW' => 0,
            'TZ' => 0,
            'UA' => 0,
            'UG' => 0,
            'US' => 0,
            'UY' => 0,
            'UZ' => 0,
            'VA' => 0,
            'VC' => 0,
            'VE' => 0,
            'VG' => 0,
            'VI' => 0,
            'VN' => 0,
            'VU' => 0,
            'WF' => 0,
            'WS' => 0,
            'YE' => 0,
            'YT' => 0,
            'ZA' => 0,
            'ZM' => 0,
            'ZW' => 0,
          ),
          'hide_single_cc' => 0,
        ),
        'default_country' => 'BE',
        'enable_country' => 1,
        'enable_default_country' => 1,
      ),
      'enable_extension' => 0,
      'entity_translation_sync' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'phone',
      'settings' => array(
        'country_code_position' => 'after',
        'extension_size' => 7,
        'label_position' => 'none',
        'number_size' => 30,
        'numbertype_allowed_values_position' => 'before',
        'use_tel_input' => 1,
      ),
      'type' => 'phone',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'business-business-field_business_vat'.
  $field_instances['business-business-field_business_vat'] = array(
    'bundle' => 'business',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'business',
    'field_name' => 'field_business_vat',
    'label' => 'VAT number',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'user-user-field_user_businesses'.
  $field_instances['user-user-field_user_businesses'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_businesses',
    'label' => 'Businesses',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'user-user-field_user_first_name'.
  $field_instances['user-user-field_user_first_name'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_first_name',
    'label' => 'First name',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => -13,
    ),
  );

  // Exported field_instance: 'user-user-field_user_last_name'.
  $field_instances['user-user-field_user_last_name'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_user_last_name',
    'label' => 'Last name',
    'required' => 1,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => -12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('BIC number');
  t('Business name');
  t('Businesses');
  t('Email address');
  t('First name');
  t('IBAN number');
  t('Invoice address');
  t('Last name');
  t('Mobile number');
  t('Phone number');
  t('VAT number');

  return $field_instances;
}
