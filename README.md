Invoicing
=========

[![Build Status](https://magnum.travis-ci.com/pfrenssen/invoicing.svg?token=zJgK3Q7yQHVpfN2zHyTH&branch=develop)](https://magnum.travis-ci.com/pfrenssen/invoicing)


Requirements
============

- [Composer](https://github.com/composer/composer)
- [Drush](https://github.com/drush-ops/drush)
- [PHP BC Math extension](http://php.net/manual/en/bc.setup.php)
- [PHP intl extension](http://php.net/manual/en/intl.installation.php)


Building
========

      $ git clone https://github.com/pfrenssen/invoicing.git
      $ cd invoicing/
      $ composer install
      $ ./vendor/bin/phing build-dev


Installing
==========

The project uses a standard Drupal installation profile. You will need the
following:

* Set up a virtualhost in your webserver using the `build/` folder as webroot.
* Create an empty database, and a database user.

Then install Drupal as usual: navigate to `/install.php` and follow the
instructions. The installation profile to use is called "Invoicing".

Alternatively you can perform everything through the command line.

    $ ./vendor/bin/phing install-dev


Docker
======

The supplied docker-compose file can be used to run the Invoicing project on a
host that has Docker and MariaDB installed. The site can be accessed at
http://localhost:8797

```bash
# Start the container.
$ docker-compose up --build

# Run a Drush command inside the container.
$ docker-compose exec php-fpm /bin/sh -c "cd /var/www/build && ../vendor/bin/drush status"
```


Podman
======

The directory `quadlet/` holds Quadlet files that run the project with rootless
Podman and systemd, on a host with Podman 6.1 or later. They start two
containers: `invoicing`, with Drupal on PHP 7.4 behind nginx, and
`invoicing-db`, with MariaDB. The image fetches the code from GitHub and builds
the site in it. Set the build argument `INVOICING_REF` in `quadlet/Containerfile`
to a commit to always get the same code.

PHP 7.4 and Drupal 7.59 no longer receive security fixes. The site listens on
`127.0.0.1:8797` only; do not expose it to the internet.

Create the secrets once. Each one is a random string of 64 hexadecimal digits:

```bash
openssl rand -hex 32 | podman secret create invoicing-db-password -
openssl rand -hex 32 | podman secret create invoicing-db-root-password -
openssl rand -hex 32 | podman secret create invoicing-hash-salt -
```

Install the files and start the site. The first start builds the image, which
takes several minutes:

```bash
podman quadlet install --application=invoicing quadlet
systemctl --user start invoicing
```

The site is at http://localhost:8797. To change the address or the port, copy
`quadlet/settings.conf.example` to
`~/.config/containers/systemd/invoicing.container.d/settings.conf`.

Run a Drush command inside the container:

```bash
podman exec --user www-data --workdir /var/www/build invoicing \
    /var/www/vendor/bin/drush status
```


Running tests
=============

Simpletest:
-----------

All our unit tests and more complicated functional tests are written in
Simpletest. They are divided in a number of test groups, each of which starting
with "Invoicing".

In order to run the tests through the user interface:
- Enable the simpletest module.
- In the browser go to admin/config/development/testing.
- Select the tests you wish to run and click "Run tests".

Alternatively, run the tests with the `run-tests.sh` script:
    $ cd ./build
    $ php ./scripts/run-tests.sh --url http://my-base-url.local/ 'Invoicing - Access','Invoicing - Business','Invoicing - Client','Invoicing - Line item','Invoicing - Invoice','Invoicing - Registration'


Behat:
------

A script is provided to make it easy to run the Behat tests. The script will
take care of setting up the environment variable that contains settings such as
the base URL that Behat needs.  The script depends on the
[drush-bde-env](https://github.com/pfrenssen/drush-bde-env) drush extension, so
make sure to install this first in your ~/.drush folder. You can then run the
script. It will ask you to enter a few configuration options and will then run
the tests:

    $ ./profiles/invoicing/behat.sh

If you want to execute the Behat tests manually, the easiest way is to also use
the `drush-bde-env` Drush extension. You can let it save a script to set up the
environment variable for Behat. You can then source this script to set the
variable:

    $ cd /path/to/drupal/root
    $ drush bes --base-url=http://my-personal-base-url.localhost config.local
    $ source config.local

Now we can run our tests:

    $ ./profiles/invoicing/vendor/bin/behat -c ./profiles/invoicing/behat.yml
