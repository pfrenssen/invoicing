#!/bin/sh
# Succeed when nginx and PHP-FPM answer without an error. The page install.php
# is used because it also works on an empty database, where Drupal 7 fails on
# every other page.
exec curl --fail --silent --output /dev/null --max-time 5 http://127.0.0.1/install.php
