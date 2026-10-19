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

Limits of the containers
------------------------

The containers limit what an attacker can do after a compromise of Drupal or
PHP:

- The network `invoicing` is internal. The containers reach each other, and
  nothing else: no internet, no other host, no DNS for outside names. The
  published port still works. Drupal therefore cannot check for updates, and
  the status report shows that HTTP requests fail.
- All capabilities are dropped, and only these are added:
  - `invoicing`: `CHOWN` (the entrypoint gives the files volume and the
    temporary directories of nginx to www-data), `SETUID` and `SETGID` (nginx
    and PHP-FPM start their workers as www-data), `NET_BIND_SERVICE` (nginx
    listens on port 80).
  - `invoicing-db`: `SETUID` and `SETGID` (the entrypoint switches to the user
    mysql), `DAC_READ_SEARCH` (the entrypoint, which runs as root, searches the
    data directory, and the health check reads its credentials from it).
- No process can gain privileges, for example through a setuid program.
- The file system of the image is read-only. Only the volumes and two tmpfs
  mounts are writable: `/tmp`, for PHP, Drupal, Drush and MariaDB, and `/run`,
  for the pid files, the socket of MariaDB and the temporary files of nginx.
  Programs on the tmpfs mounts cannot run.
- Memory and the number of processes are limited: 192 MB and 64 processes for
  `invoicing`, 192 MB and 128 for `invoicing-db`. The tmpfs mounts count as
  memory. A PHP request may use up to 128 MB, and the buffer pool of MariaDB is
  32 MB.
- PHP accepts no file uploads, and a request body is at most 2 MB. A form with
  a file field, such as the import of a translation, receives no file.

The OCI runtime has to be crun. With runc, a container with a read-only file
system cannot mount the secrets, and fails to start with
`make mountpoint "/run/secrets/…": read-only file system`
([podman#15541](https://github.com/containers/podman/issues/15541)). Podman
uses crun when it is installed: `podman info --format
'{{.Host.OCIRuntime.Name}}'` shows the runtime.

A change that needs another capability fails with an error such as
`Operation not permitted` or `Permission denied` in the journal:

```bash
journalctl --user -u invoicing -u invoicing-db
```

Find the operation in the error and the capability that allows it in
`capabilities(7)`, for example `setuid()` and `CAP_SETUID`. Add one capability
at a time to `AddCapability=`, and start the unit again. An error about a
read-only file system means that the program writes outside the volumes and the
tmpfs mounts; change its path to one in `/tmp` or `/run` instead of making the
file system writable.


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
