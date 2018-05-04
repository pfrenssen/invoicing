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
