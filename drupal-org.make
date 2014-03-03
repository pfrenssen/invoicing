api = 2
core = 7.x

projects[addressfield][download][type] = git
projects[addressfield][download][revision] = 7.x-1.0-beta5
projects[addressfield][download][branch] = 7.x-1.x
projects[addressfield][subdir] = contrib

projects[ctools][download][type] = git
projects[ctools][download][revision] = 7.x-1.4
projects[ctools][download][branch] = 7.x-1.x
projects[ctools][subdir] = contrib

projects[email][download][type] = git
projects[email][download][revision] = 7.x-1.2
projects[email][download][branch] = 7.x-1.x
projects[email][subdir] = contrib

projects[entity][download][type] = git
projects[entity][download][revision] = 7.x-1.2
projects[entity][download][branch] = 7.x-1.x
projects[entity][subdir] = contrib

projects[entityreference][download][type] = git
projects[entityreference][download][revision] = 7.x-1.1
projects[entityreference][download][branch] = 7.x-1.x
projects[entityreference][subdir] = contrib

projects[entityreference_unique][download][type] = git
projects[entityreference_unique][download][revision] = 7.x-1.0-alpha1
projects[entityreference_unique][download][branch] = 7.x-1.x
projects[entityreference_unique][subdir] = contrib

; Issue #2206905: Notice when entity does not have bundle.
; @see https://drupal.org/node/2206905
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2206905-3-entityreference_unique-notice.patch

; Issue #2209127: Improve validation message.
; @see https://drupal.org/node/2209127
projects[entityreference_unique][patch][] = http://drupal.org/files/issues/2209127-1-entityreference_unique-validation_message.patch

projects[features][download][type] = git
projects[features][download][revision] = 7.x-2.0
projects[features][download][branch] = 7.x-2.x
projects[features][subdir] = contrib

projects[views][download][type] = git
projects[views][download][revision] = 7.x-3.7
projects[views][download][branch] = 7.x-3.x
projects[views][subdir] = contrib
