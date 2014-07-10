api = 2
core = 7.x

projects[drupal][version] = 7.28

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

projects[addressfield] = 1.0-beta5
projects[addressfield][subdir] = contrib

projects[ctools] = 1.4
projects[ctools][subdir] = contrib

projects[date] = 2.7
projects[date][subdir] = contrib

projects[email] = 1.2
projects[email][subdir] = contrib

projects[email_registration] = 1.2
projects[email_registration][subdir] = contrib

projects[entity] = 1.4
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

projects[entityreference_unique] = 7.x-1.0-alpha1
projects[entityreference_unique][subdir] = contrib

; Issue #2206905: Notice when entity does not have bundle.
; @see https://drupal.org/node/2206905
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2206905-3-entityreference_unique-notice.patch

; Issue #2209127: Improve validation message.
; @see https://drupal.org/node/2209127
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2209127-1-entityreference_unique-validation_message.patch

projects[features] = 2.0
projects[features][subdir] = contrib

; The dev branch has been pinned at the time the below patch was created.
projects[inline_entity_form][download][type] = git
projects[inline_entity_form][download][revision] = 8229859b9c8f2bcf58fa683cd29b3b79243de290
projects[inline_entity_form][download][branch] = 7.x-1.x
projects[inline_entity_form][subdir] = contrib

; Issue #2134035: Allow to add existing entities using the single value field
; widget.
; @see https://www.drupal.org/node/2134035
projects[inline_entity_form][patch][] = https://www.drupal.org/files/issues/2134035-28-inline_entity_form-add_existing_single_value.patch

projects[link] = 1.2
projects[link][subdir] = contrib

projects[phone_libphonenumber][type] = module
projects[phone_libphonenumber][download][type] = git
projects[phone_libphonenumber][download][branch] = 7.x-1.x
projects[phone_libphonenumber][download][revision] = 995a080
projects[phone_libphonenumber][download][url] = http://git.drupal.org/sandbox/cdale/1925578.git
projects[phone_libphonenumber][subdir] = contrib

; Issue #2214569: Use the current fork of libphonenumber by giggsey.
; @see https://www.drupal.org/node/2214569
projects[phone_libphonenumber][patch][] = https://www.drupal.org/files/issues/2214569-2-phone_libphonenumber-update_library.patch

projects[strongarm] = 2.0
projects[strongarm][subdir] = contrib

; The current release of the module is old so we use the newest release
; candidate.
projects[user_registrationpassword][download][type] = git
projects[user_registrationpassword][download][revision] = 235d87e90077d53a8c6cdf028a38ff0891baa4f7
projects[user_registrationpassword][download][branch] = 7.x-1.x
projects[user_registrationpassword][subdir] = contrib

projects[views] = 3.7
projects[views][subdir] = contrib
