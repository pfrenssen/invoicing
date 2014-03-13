api = 2
core = 7.x

projects[addressfield] = 1.0-beta5
projects[addressfield][subdir] = contrib

projects[ctools] = 1.4
projects[ctools][subdir] = contrib

projects[email] = 1.2
projects[email][subdir] = contrib

projects[entity] = 1.2
projects[entity][subdir] = contrib

projects[entityreference] = 1.1
projects[entityreference][subdir] = contrib

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

projects[strongarm] = 2.0
projects[strongarm][subdir] = contrib

projects[views] = 3.7
projects[views][subdir] = contrib
