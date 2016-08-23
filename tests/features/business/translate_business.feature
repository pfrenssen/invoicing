Feature: Translate my business
  In order to do present my business info to international clients
  As a business owner
  I want to be able to translate my business in a different language

@api @javascript
Scenario: Translate my business to Bulgarian
  Given I am logged in as a user with the "business owner" role
  When I visit my business page
  And I click "Translate"
  Then I should see "Add translation" in the "Bulgarian" row
  And I should see "Edit translation" in the "English" row
  When I click "Add translation" in the "Bulgarian" row
  And I select "Bulgaria" from "Country"
  And I enter the following:
  | Business name | Коуд Лаб ЕООД                    |
  | Address 1     | ул. Люлякова градина No 7, ап. 3 |
  | City          | София                            |
  And I press "Save"
  Then I should see the success message "The changes have been saved."
  And I should see the heading "Коуд Лаб ЕООД [Bulgarian]"
  And the "Business name" field should contain "Коуд Лаб ЕООД"
  And the "Address 1" field should contain "ул. Люлякова градина No 7, ап. 3"
  And the "City" field should contain "София"
  When I click "Translate"
  Then I should see "Edit translation" in the "Bulgarian" row
