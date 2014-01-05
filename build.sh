#!/bin/bash

# Builds the Invoicing distribution.
#
# Options:
# --git: Retain the git repositories of all downloaded projects.

ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BUILD_DIR="${ROOT_DIR}/build"
DRUSH_MAKE_OPTIONS=""

# Print out documentation.
function show_help {
  echo -e "Usage: ./build.sh [OPTIONS]"
  echo -e "Builds the Invoicing distribution in the 'build' subfolder. Options:"
  echo -e "-h\t--help\tShow this help text."
  echo -e "-g\t--git\tRetain the git repositories of all downloaded projects."
}

# Check command line arguments.
while [[ "$1" == -* ]]; do
  case "$1" in
    -h|--help|-\?) show_help; exit 0;;
    -g|--git) GIT=true; shift;;
    -b|--branded) BRANDED=true; shift;;
    --) shift; break;;
    -*) echo "invalid option: $1" 1>&2; show_help; exit 1;;
  esac
done

# Do not continue if the distribution was already built.
if [ -d "${BUILD_DIR}" ] ; then
  echo "Error: Target directory already exists: ${BUILD_DIR}"
  echo "Please rename or remove this directory before continuing."
  exit 1
fi

# Set up Drush make options
if [ $GIT ] ; then
  DRUSH_MAKE_OPTIONS="$DRUSH_MAKE_OPTIONS --working-copy"
fi

# Move the distribution files into a profile.
mkdir -p "${BUILD_DIR}/profiles/invoicing"
find "${ROOT_DIR}" -mindepth 1 -maxdepth 1 ! -iname "build" -exec cp -r {} "${BUILD_DIR}/profiles/invoicing/" \;

cd "${BUILD_DIR}"

# Install Drupal core.
drush make --prepare-install --drupal-org=core "${ROOT_DIR}/drupal-org-core.make" -y $DRUSH_MAKE_OPTIONS
if [ $? -ne 0 ] ; then { echo "error: Drupal core build failed" ; exit 1 ; } fi

# Install contrib.
drush make --contrib-destination=profiles/invoicing "${ROOT_DIR}/drupal-org.make" -y $DRUSH_MAKE_OPTIONS --drupal-org
if [ $? -ne 0 ] ; then { echo "error: contributed modules could not be built" ; exit 1 ; } fi

# Remove all .git directories if they are not needed.
if [ -z $GIT ] ;  then
  find . -type d -name ".git" -print0 | xargs -0 rm -rf
fi

cd "${ROOT_DIR}"

echo -e "\nBuild is available in ${BUILD_DIR}."

exit 0
