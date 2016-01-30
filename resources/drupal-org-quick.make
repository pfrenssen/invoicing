api = 2
core = 7.x

projects[drupal][version] = 7.37

; Recursive module dependencies of installation profile are not enabled in
; DrupalWebTestCase::setUp.
; @see https://drupal.org/node/1093420
projects[drupal][patch][] = http://drupal.org/files/simpletest-module_enable_dependencies-1093420-9.patch

; Remove static cache in drupal_valid_test_ua().
; @see https://drupal.org/node/1436684
projects[drupal][patch][] = http://drupal.org/files/1436684_failing_tests_d7.patch

; DrupalWebTestCase::buildXPathQuery() tries to handle backreferences in
; argument values.
; @see https://drupal.org/node/1988780
projects[drupal][patch][] = http://drupal.org/files/1988780-6-simpletest-backreferences.patch

; prepareInstallDirectory() doesn't create installation directory.
; @see https://drupal.org/node/2061333
projects[drupal][patch][] = http://drupal.org/files/updater-installation_directory_not_created-2061333-1.patch

; DrupalWebTestCase::drupalGetToken() does not add hash salt.
; @see https://www.drupal.org/node/1555862
projects[drupal][patch][] = http://drupal.org/files/issues/1555862-38-drupalGetToken_hash_salt-D7-do-not-test.patch

; run-tests.sh should exit with a failure code if any tests failed.
; @see https://www.drupal.org/node/2189345
projects[drupal][patch][] = http://www.drupal.org/files/issues/d7-run_tests_sh_should-2189345-34-do-not-test.patch

projects[addressfield][version] = 1.1
projects[addressfield][subdir] = contrib

projects[composer_manager][version] = 1.8
projects[composer_manager][subdir] = contrib

projects[ctools][version] = 1.9
projects[ctools][subdir] = contrib

; PHP 4 style constructors are deprecated in PHP 7.
; @see https://www.drupal.org/node/2528736
projects[ctools][patch][] = https://www.drupal.org/files/issues/deprecating_php4_style-2528736-23.patch

projects[date][version] = 2.8
projects[date][subdir] = contrib

projects[elements][version] = 1.4
projects[elements][subdir] = contrib

; Allow autocomplete on number field.
; @see https://www.drupal.org/node/2459025
projects[elements][patch][] = http://www.drupal.org/files/issues/2459025-1.patch

projects[email][version] = 1.3
projects[email][subdir] = contrib

projects[email_registration][version] = 1.2
projects[email_registration][subdir] = contrib

projects[entity][version] = 1.6
projects[entity][subdir] = contrib

; entity_metadata_wrapper() does not load correct revisions.
; @see https://drupal.org/node/1788568
projects[entity][patch][] = https://drupal.org/files/issues/entity-1788568-12-entity_metadata_wrapper_revisions.patch

; A recent version is pinned so that the patches can be applied.
projects[entityreference][download][type] = git
projects[entityreference][download][revision] = dc4196b4e97e11ff
projects[entityreference][download][branch] = 7.x-1.x
projects[entityreference][subdir] = contrib

; Issue #2266735: Entity labels are not sanitized consistently.
; @see https://drupal.org/node/2266735
projects[entityreference][patch][] = https://drupal.org/files/issues/2266735-2-entityreference-inconsistent_sanitizing.patch

; Issue #1837650: Allow referencing a specific revision ID.
; @see https://drupal.org/node/1837650
projects[entityreference][patch][] = https://drupal.org/files/issues/entityreference-n1837650-47.patch

projects[entityreference_unique][version] = 1.0-beta2
projects[entityreference_unique][subdir] = contrib

; Issue #2206905: Notice when entity does not have bundle.
; @see https://drupal.org/node/2206905
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2206905-3-entityreference_unique-notice.patch

; Issue #2209127: Improve validation message.
; @see https://drupal.org/node/2209127
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2209127-1-entityreference_unique-validation_message.patch

projects[features][version] = 2.4
projects[features][subdir] = contrib

; The dev branch has been pinned at the time the below patch was created.
projects[inline_entity_form][download][type] = git
projects[inline_entity_form][download][revision] = 887eec888030a43daaa7265809c105663baa3ff8
projects[inline_entity_form][download][branch] = 7.x-1.x
projects[inline_entity_form][subdir] = contrib

; Issue #2134035: Allow to add existing entities using the single value field
; widget.
; @see https://www.drupal.org/node/2134035
projects[inline_entity_form][patch][] = http://www.drupal.org/files/issues/inline_entity_form-allow-to-add-existing-2134035-52.patch

projects[ief_autocomplete][type] = module
projects[ief_autocomplete][download][type] = git
projects[ief_autocomplete][download][branch] = 7.x-1.x
projects[ief_autocomplete][download][url] = http://git.drupal.org/sandbox/iSoLate/2363793.git
projects[ief_autocomplete][subdir] = contrib

projects[link][version] = 1.3
projects[link][subdir] = contrib

; A recent dev release of Panels is pinned since it contains a number of PHP 7
; fixes. Revert to the stable release when 7.x-3.6 is released.
projects[panels][download][type] = git
projects[panels][download][revision] = e8623b704fb2585bbf77f31f06d4a98721556277
projects[panels][download][branch] = 7.x-3.x
projects[panels][subdir] = contrib

projects[phone][type] = module
projects[phone][download][type] = git
projects[phone][download][branch] = master
projects[phone][download][revision] = 655b57f96e9
projects[phone][download][url] = http://git.drupal.org/sandbox/cdale/1925578.git
projects[phone][subdir] = contrib

projects[strongarm][version] = 2.0
projects[strongarm][subdir] = contrib

; The current release of the module is old so we use the newest release
; candidate.
projects[user_registrationpassword][download][type] = git
projects[user_registrationpassword][download][revision] = 6963288
projects[user_registrationpassword][download][branch] = 7.x-1.x
projects[user_registrationpassword][subdir] = contrib

projects[views][version] = 3.13
projects[views][subdir] = contrib
