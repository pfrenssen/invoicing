FROM php:7.4-fpm-alpine

# Run as the user "fpm" with UID 1000 and GID 1000, matching the host user.
RUN addgroup -g 1000 -S fpm && adduser -u 1000 -S fpm -G fpm

# Install necessary PHP extensions.
# Also install the mysql client. Drush needs it to connect to the database.
# Ref. https://drupal.stackexchange.com/questions/251309/php-fatal-error-uncaught-error-call-to-undefined-function-cache-get
# Ref. https://github.com/drush-ops/drush/issues/4884
RUN apk add --no-cache libpng-dev libjpeg-turbo-dev freetype-dev mysql-client \
    && docker-php-ext-configure gd --with-freetype --with-jpeg \
    && docker-php-ext-install gd mysqli pdo pdo_mysql opcache bcmath

USER fpm

WORKDIR /var/www

# Expose port 9000 for PHP-FPM.
EXPOSE 9000

CMD ["php-fpm"]
