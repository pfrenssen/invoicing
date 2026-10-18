#!/bin/sh
# Succeed when the site answers without an error. A site that is not installed
# yet answers with a redirect to install.php, which counts as healthy.
exec curl --fail --silent --output /dev/null --max-time 5 http://127.0.0.1/
