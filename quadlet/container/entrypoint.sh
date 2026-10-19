#!/bin/sh
# Prepare the files directory of Drupal and start supervisord, which runs
# PHP-FPM and nginx.
set -eu

FILES=/var/www/build/sites/default/files

# The volume is empty at the first start, and owned by root. PHP-FPM runs as
# www-data and has to write here.
mkdir -p "$FILES/private"
chown www-data:www-data "$FILES" "$FILES/private"

# The temporary files of nginx. /run is an empty tmpfs at each start. nginx
# finds the directories with the right owner, and does not have to create them.
mkdir -p /run/nginx/body /run/nginx/fastcgi /run/nginx/proxy /run/nginx/scgi \
    /run/nginx/uwsgi
chown -R www-data:www-data /run/nginx

exec supervisord --configuration /etc/supervisord.conf
