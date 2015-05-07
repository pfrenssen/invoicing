#!/bin/bash

# Runs behat tests from the site root. This ensures that the DRUPAL_ROOT
# constant is set correctly.
#
# Install the 'drush-bde-env' drush command before running the script. You can
# get it from https://github.com/pfrenssen/drush-bde-env
#
# When the script is first ran you will be asked for the location of the drush
# executable, and the base URL of the website. These settings can be saved in a
# local file so they can be reused.
#
# Any parameters you add will be passed to Behat. Examples:
#
# # Run all tests.
# $ ./behat.sh
#
# # Run a single test.
# $ ./behat.sh features/create_invoice.feature
#
# # List the available step definitions.
# $ ./behat.sh -di

# A list of the configuration variables.
CONFIG_VARIABLES=( "BASE_URL" "DRUSH" )

# Load config file if it exists.
if [ -f behat.config ] ; then
  . behat.config
fi

# Get user input for missing parameters.
while [ -z "$DRUSH" ] ; do
  read -p "Path to drush (e.g. '/usr/bin/drush'): " DRUSH
  if ! $DRUSH st &> /dev/null ; then
    echo 'Error, could not execute drush. Please try again.'
    DRUSH=

  # Check if drush-bde-env is installed.
  elif ! $DRUSH bde-env-gen &> /dev/null ; then
    echo 'Please install the drush-bde-env drush command before continuing.'
    echo 'See https://github.com/pfrenssen/drush-bde-env'
    exit 1
  fi
done

while [ -z "$BASE_URL" ] ; do
  read -p "Base URL (e.g. 'http://invoicing.local'): " BASE_URL
done

# Save configuration.
if [ ! -f behat.config ]; then
  read -p "Do you want to save these settings (y/n)? " SAVE_CONFIG
  if [ "$SAVE_CONFIG" == "y" ] ; then
    for CONFIG_VARIABLE in ${CONFIG_VARIABLES[@]} ; do
      echo "$CONFIG_VARIABLE=\"${!CONFIG_VARIABLE}\"" >> behat.config
    done
  fi
fi

# Retrieve site paths.
ROOT_PATH=`$DRUSH dd`
PROFILE_PATH=`$DRUSH dd invoicing`
BIN_PATH=$PROFILE_PATH/vendor/bin

# Navigate to the root path so DRUPAL_ROOT is set correctly.
cd $ROOT_PATH

eval $($DRUSH bde-env-gen --base-url=$BASE_URL)

$BIN_PATH/behat -c $PROFILE_PATH/behat.yml "$@"

