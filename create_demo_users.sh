#!/bin/bash

# This script will create some demo users to test with:
# - administrator
# - authenticated user
# - business owner
# - client
#
# Use the password "demo" for each of these users.
#
# Disclaimer: this is only intended to be used in controlled environments for
# demonstration purposes. Do not use this on websites that are publicly
# accessible.

# Execute the drush commands from within the site.
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${ROOT_DIR}"

# Create the users.
drush user-create administrator --mail="administrator@example.com" --password="demo"
drush user-create "authenticated user" --mail="authenticated_user@example.com" --password="demo"
drush user-create "business owner" --mail="business_owner@example.com" --password="demo"
drush user-create client --mail="client@example.com" --password="demo"

# Add the roles to the users.
drush user-add-role administrator administrator
drush user-add-role "authenticated user" "authenticated user"
drush user-add-role "business owner" "business owner"
drush user-add-role client client

exit 0
