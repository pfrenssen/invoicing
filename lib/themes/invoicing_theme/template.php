<?php

/**
 * @file
 * Theme hook overrides and (pre-)process functions for the Invoicing theme.
 */

/**
 * Theme the entity translation overview table.
 */
function invoicing_theme_entity_translation_overview_table($variables) {
  $entity_type = $variables['entity_type'];
  $entity = $variables['entity'];

  $handler = entity_translation_get_handler($entity_type, $entity);
  $handler->initPathScheme();

  // Initialize translations if they are empty.
  $translations = $handler->getTranslations();
  if (empty($translations->original)) {
    $handler->initTranslations();
    $handler->saveTranslations();
  }

  // Ensure that we have a coherent status between entity language and field
  // languages.
  if ($handler->initOriginalTranslation()) {
    // FIXME!
    field_attach_presave($entity_type, $entity);
    field_attach_update($entity_type, $entity);
  }

  $header = array(t('Language'), t('Operations'));
  $languages = entity_translation_languages();
  $source = $translations->original;
  $path = $handler->getViewPath();
  $rows = array();

  if (drupal_multilingual()) {
    // If we have a view path defined for the current entity get the switch
    // links based on it.
    if ($path) {
      $links = EntityTranslationDefaultHandler::languageSwitchLinks($path);
    }

    foreach ($languages as $language) {
      $classes = array();
      $options = array();
      $language_name = $language->name;
      $langcode = $language->language;
      $edit_path = $handler->getEditPath($langcode);
      $add_path = "{$handler->getEditPath()}/add/$source/$langcode";

      if ($edit_path) {
        $add_links = EntityTranslationDefaultHandler::languageSwitchLinks($add_path);
        $edit_links = EntityTranslationDefaultHandler::languageSwitchLinks($edit_path);
      }

      if (isset($translations->data[$langcode])) {
        // Existing translation in the translation set: display status.
        $translation = $translations->data[$langcode];
        $link = isset($links->links[$langcode]['href']) ? $links->links[$langcode] : array('href' => $path, 'language' => $language);
        $language_name = l($language_name, $link['href'], $link);

        if ($edit_path && $handler->getAccess('update') && $handler->getTranslationAccess($langcode)) {
          $link = isset($edit_links->links[$langcode]['href']) ? $edit_links->links[$langcode] : array('href' => $edit_path, 'language' => $language);
          $link['query'] = isset($_GET['destination']) ? drupal_get_destination() : FALSE;
          $options[] = l(t('edit'), $link['href'], $link);
        }

        $classes[] = $translation['status'] ? 'published' : 'not-published';
        $classes[] = isset($translation['translate']) && $translation['translate'] ? 'outdated' : '';

      }
      else {
        if ($source != $langcode && $handler->getAccess('update') && $handler->getTranslationAccess($langcode)) {
          list(, , $bundle) = entity_extract_ids($entity_type, $entity);
          $translatable = FALSE;

          foreach (field_info_instances($entity_type, $bundle) as $instance) {
            $field_name = $instance['field_name'];
            $field = field_info_field($field_name);
            if ($field['translatable']) {
              $translatable = TRUE;
              break;
            }
          }

          $link = isset($add_links->links[$langcode]['href']) ? $add_links->links[$langcode] : array('href' => $add_path, 'language' => $language);
          $link['query'] = isset($_GET['destination']) ? drupal_get_destination() : FALSE;
          $options[] = $translatable ? l(t('add'), $link['href'], $link) : t('No translatable fields');
          $classes[] = $translatable ? '' : 'non-translatable';
        }
      }
      $rows[] = array(
        'data' => array($language_name, implode(" | ", $options)),
        'class' => $classes,
      );
    }
  }

  return theme('entity_translation_overview', array(
    'header' => $header,
    'rows' => $rows,
  ));
}
