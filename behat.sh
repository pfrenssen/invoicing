#!/bin/bash

ROOT_PATH=`drush dd`
PROFILE_PATH=`drush dd invoicing`
BIN_PATH=$PROFILE_PATH/vendor/bin

# Navigate to the root path so DRUPAL_ROOT is set correctly.
cd $ROOT_PATH

$BIN_PATH/behat -c $PROFILE_PATH/behat.yml "$@"

