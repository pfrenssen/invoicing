api = 2
core = 7.x

projects[drupal][type] = core
projects[drupal][download][type] = git
projects[drupal][download][revision] = 7.43
projects[drupal][download][branch] = 7.x

; Recursive module dependencies of installation profile are not enabled in
; DrupalWebTestCase::setUp.
; https://drupal.org/node/1093420
projects[drupal][patch][] = http://drupal.org/files/simpletest-module_enable_dependencies-1093420-9.patch

; Remove static cache in drupal_valid_test_ua().
; https://drupal.org/node/1436684
projects[drupal][patch][] = http://drupal.org/files/1436684_failing_tests_d7.patch

; DrupalWebTestCase::buildXPathQuery() tries to handle backreferences in
; argument values.
; https://drupal.org/node/1988780
projects[drupal][patch][] = http://drupal.org/files/1988780-6-simpletest-backreferences.patch

; prepareInstallDirectory() doesn't create installation directory.
; https://drupal.org/node/2061333
projects[drupal][patch][] = http://drupal.org/files/updater-installation_directory_not_created-2061333-1.patch

; DrupalWebTestCase::drupalGetToken() does not add hash salt.
; https://www.drupal.org/node/1555862
projects[drupal][patch][] = http://drupal.org/files/issues/1555862-38-drupalGetToken_hash_salt-D7-do-not-test.patch

; run-tests.sh should exit with a failure code if any tests failed.
; https://www.drupal.org/node/2189345
projects[drupal][patch][] = http://www.drupal.org/files/issues/d7-run_tests_sh_should-2189345-34-do-not-test.patch

; _drupal_session_destroy() should return boolean.
; https://www.drupal.org/node/2460833
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-session_destroy_return_bool-2460833-21-D7.patch

projects[addressfield][download][type] = git
projects[addressfield][download][revision] = 7.x-1.1
projects[addressfield][download][branch] = 7.x-1.x
projects[addressfield][subdir] = contrib

projects[composer_manager][download][type] = git
projects[composer_manager][download][revision] = 7.x-1.8
projects[composer_manager][download][branch] = 7.x-1.x
projects[composer_manager][subdir] = contrib

; Simpletests break when vendor folder is different than the default.
; https://www.drupal.org/node/2660024
projects[composer_manager][patch][] = https://www.drupal.org/files/issues/2660024-2-remove-workaround.patch

projects[ctools][download][type] = git
projects[ctools][download][revision] = 7.x-1.9
projects[ctools][download][branch] = 7.x-1.x
projects[ctools][subdir] = contrib

; PHP 4 style constructors are deprecated in PHP 7.
; https://www.drupal.org/node/2528736
projects[ctools][patch][] = https://www.drupal.org/files/issues/deprecating_php4_style-2528736-23.patch

projects[date][download][type] = git
projects[date][download][revision] = 7.x-2.8
projects[date][download][branch] = 7.x-2.x
projects[date][subdir] = contrib

projects[elements][download][type] = git
projects[elements][download][revision] = 7.x-1.4
projects[elements][download][branch] = 7.x-1.x
projects[elements][subdir] = contrib

; Allow autocomplete on number field.
; https://www.drupal.org/node/2459025
projects[elements][patch][] = http://www.drupal.org/files/issues/2459025-1.patch

projects[email][download][type] = git
projects[email][download][revision] = 7.x-1.3
projects[email][download][branch] = 7.x-1.x
projects[email][subdir] = contrib

projects[email_registration][download][type] = git
projects[email_registration][download][revision] = 7.x-1.2
projects[email_registration][download][branch] = 7.x-1.x
projects[email_registration][subdir] = contrib

projects[entity][download][type] = git
projects[entity][download][revision] = 7.x-1.6
projects[entity][download][branch] = 7.x-1.x
projects[entity][subdir] = contrib

; entity_metadata_wrapper() does not load correct revisions.
; https://drupal.org/node/1788568
projects[entity][patch][] = https://drupal.org/files/issues/entity-1788568-12-entity_metadata_wrapper_revisions.patch

; A recent version is pinned so that the patches can be applied.
projects[entityreference][download][type] = git
projects[entityreference][download][revision] = dc4196b4e97e11ff
projects[entityreference][download][branch] = 7.x-1.x
projects[entityreference][subdir] = contrib

; Issue #2266735: Entity labels are not sanitized consistently.
; https://drupal.org/node/2266735
projects[entityreference][patch][] = https://drupal.org/files/issues/2266735-2-entityreference-inconsistent_sanitizing.patch

; Issue #1837650: Allow referencing a specific revision ID.
; https://drupal.org/node/1837650
projects[entityreference][patch][] = https://drupal.org/files/issues/entityreference-n1837650-47.patch

projects[entityreference_unique][download][type] = git
projects[entityreference_unique][download][revision] = 7.x-1.0-beta2
projects[entityreference_unique][download][branch] = 7.x-1.x
projects[entityreference_unique][subdir] = contrib

; Issue #2206905: Notice when entity does not have bundle.
; https://drupal.org/node/2206905
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2206905-3-entityreference_unique-notice.patch

; Issue #2209127: Improve validation message.
; https://drupal.org/node/2209127
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2209127-1-entityreference_unique-validation_message.patch

projects[entity_translation][download][type] = git
projects[entity_translation][download][revision] = 7.x-1.0-beta4
projects[entity_translation][download][branch] = 7.x-1.x
projects[entity_translation][subdir] = contrib

; Issue #2710879: Allow to properly theme the translation overview.
; https://drupal.org/node/2710879
projects[entity_translation][patch][] = https://www.drupal.org/files/issues/2710879-2.patch

projects[features][download][type] = git
projects[features][download][revision] = 7.x-2.7
projects[features][download][branch] = 7.x-2.x
projects[features][subdir] = contrib

; The dev branch has been pinned at the time the below patch was created.
projects[inline_entity_form][download][type] = git
projects[inline_entity_form][download][revision] = 8d8ee06592d991
projects[inline_entity_form][download][branch] = 7.x-1.x
projects[inline_entity_form][subdir] = contrib

; Issue #2134035: Allow to add existing entities using the single value field
; widget.
; https://www.drupal.org/node/2134035
projects[inline_entity_form][patch][] = https://www.drupal.org/files/issues/inline_entity_form-allow-to-add-existing-2134035-76.patch

projects[ief_autocomplete][type] = module
projects[ief_autocomplete][download][type] = git
projects[ief_autocomplete][download][branch] = 7.x-1.x
projects[ief_autocomplete][download][url] = http://git.drupal.org/sandbox/iSoLate/2363793.git
projects[ief_autocomplete][subdir] = contrib

projects[link][download][type] = git
projects[link][download][revision] = 7.x-1.3
projects[link][download][branch] = 7.x-1.x
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

projects[strongarm][download][type] = git
projects[strongarm][download][revision] = 7.x-2.0
projects[strongarm][download][branch] = 7.x-2.x
projects[strongarm][subdir] = contrib

; The current release of the module is old so we use the newest release
; candidate.
projects[user_registrationpassword][download][type] = git
projects[user_registrationpassword][download][revision] = 6963288
projects[user_registrationpassword][download][branch] = 7.x-1.x
projects[user_registrationpassword][subdir] = contrib

projects[views][download][type] = git
projects[views][download][revision] = 7.x-3.13
projects[views][download][branch] = 7.x-3.x
projects[views][subdir] = contrib
