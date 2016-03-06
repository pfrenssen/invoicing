<?php

/**
 * Business translation handler.
 */
class EntityTranslationBusinessHandler extends EntityTranslationDefaultHandler {

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
