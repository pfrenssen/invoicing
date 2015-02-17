Invoicing
=========

[![Build Status](https://magnum.travis-ci.com/pfrenssen/invoicing.svg?token=zJgK3Q7yQHVpfN2zHyTH&branch=develop)](https://magnum.travis-ci.com/pfrenssen/invoicing)


Requirements
============

- [Composer](https://github.com/composer/composer)
- [Drush](https://github.com/drush-ops/drush)
- [PHP intl extension](http://php.net/manual/en/intl.installation.php)


Building
========

* Clone the repository from GitHub.

      $ git clone https://github.com/pfrenssen/invoicing.git

* Build the project by running the `build.sh` script. You can list the
  available options by passing the `--help` option. The build will be created in
  a subfolder named "build". For example to do a quick build with error logging:

      $ cd invoicing/
      $ ./build.sh --quick --verbose


Installing
==========

The project uses a standard Drupal installation profile. You will need the
following:

* Set up a virtualhost in your webserver using the `build/` folder as webroot.
* Create an empty database, and a database user.

Then install Drupal as usual: navigate to `/install.php` and follow the
instructions. The installation profile to use is called "Invoicing".

Alternatively you can perform everything through the command line. Here's an
example assuming you created a MySQL database called 'invoicing' and a user
with the username 'invoicing' and password 'invoicing':

    $ cd ./build
    # Create files folder, copy settings.php and set permissions.
    $ cp sites/default/default.settings.php sites/default/settings.php
    $ chmod 777 sites/default/settings.php
    $ mkdir -p sites/default/files
    $ chmod 775 sites/default/files
    $ drush si --account-name=admin --account-pass=admin --db-url=mysql://invoicing:invoicing@localhost/invoicing invoicing -y --debug

Also, make sure to install the composer dependencies:
    $ cd ./profiles/invoicing
    $ composer install


Running tests
=============

Simpletest:

All our unit tests and more complicated functional tests are written in
Simpletest. They are divided in a number of test groups, each of which starting
with "Invoicing".

In order to run the tests through the user interface:
- Enable the simpletest module.
- In the browser go to admin/config/development/testing.
- Select the tests you wish to run and click "Run tests".

Alternatively, run the tests with drush:
$ drush test-run 'Invoicing - Access','Invoicing - Business','Invoicing - Client','Invoicing     - Line item','Invoicing - Invoice','Invoicing - Registration' --uri=http://my-base-url.local

Behat:

In order to run Behat tests we need to first set some environment variables. The
easiest way to do this is by installing the
[drush-bde-env](https://github.com/pfrenssen/drush-bde-env) drush extension and
running the following command:

$ cd /path/to/drupal/root
$ drush bes --base-url=http://my-personal-base-url.localhost config.local
$ source config.local

Now we can run our tests:
$ ./profiles/invoicing/vendor/bin/behat -c ./profiles/invoicing/behat.yml
