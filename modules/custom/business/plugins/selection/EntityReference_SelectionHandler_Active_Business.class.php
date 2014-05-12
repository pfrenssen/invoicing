<?php

/**
 * @file
 * Entity Reference selection handler that filters on the active business.
 */
class EntityReference_SelectionHandler_Active_Business extends EntityReference_SelectionHandler_Generic {

  /**
   * {@inheritdoc}
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new EntityReference_SelectionHandler_Active_Business($field, $instance, $entity_type, $entity);
  }

  /**
   * {@inheritdoc}
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    $options = array();
    $entity_type = $this->field['settings']['target_type'];

    $query = $this->buildEntityFieldQuery($match, $match_operator);
    if ($limit > 0) {
      $query->range(0, $limit);
    }

    // Filter on the active business.
    $query->propertyCondition('bid', business_get_active_business()->identifier());

    $results = $query->execute();

    if (!empty($results[$entity_type])) {
      $entities = entity_load($entity_type, array_keys($results[$entity_type]));
      foreach ($entities as $entity_id => $entity) {
        list(,, $bundle) = entity_extract_ids($entity_type, $entity);
        $options[$bundle][$entity_id] = check_plain($this->getLabel($entity));
      }
    }

    return $options;
  }

}
