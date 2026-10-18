<?php

/**
 * @file
 * Drupal settings of the Invoicing container.
 *
 * The database password and the hash salt are podman secrets, mounted as files.
 */

$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => 'invoicing',
  'username' => 'invoicing',
  'password' => trim(file_get_contents('/run/secrets/db_password')),
  'host' => 'db',
  'port' => '3306',
  'prefix' => '',
  'charset' => 'utf8mb4',
  'collation' => 'utf8mb4_general_ci',
);

$drupal_hash_salt = trim(file_get_contents('/run/secrets/hash_salt'));
