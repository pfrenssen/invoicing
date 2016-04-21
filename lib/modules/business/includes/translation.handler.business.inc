<?php

/**
 * @file
 * Contains \EntityTranslationBusinessHandler.
 */

/**
 * Business translation handler.
 */
class EntityTranslationBusinessHandler extends EntityTranslationDefaultHandler {

  /**
   * Constructs an EntityTranslationBusinessHandler object.
   *
   * @param string $entity_type
   *   The type of the entity being wrapped.
   * @param string $entity_info
   *   The entity information for the entity being wrapped.
   * @param string $entity
   *   The entity being wrapped.
   */
  public function __construct($entity_type, $entity_info, $entity) {
    parent::__construct('business', $entity_info, $entity);
  }

  /**
   * Hide the translation fieldset.
   */
  public function entityForm(&$form, &$form_state) {
    parent::entityForm($form, $form_state);

    $form['translation']['#access'] = FALSE;
  }

}
