#!/bin/sh
# Prepare the files directory of Drupal and start supervisord, which runs
# PHP-FPM and nginx.
set -eu

FILES=/var/www/build/sites/default/files

# The volume is empty at the first start, and owned by root. PHP-FPM runs as
# www-data and has to write here.
mkdir -p "$FILES/private"
chown www-data:www-data "$FILES" "$FILES/private"

exec supervisord --configuration /etc/supervisord.conf
