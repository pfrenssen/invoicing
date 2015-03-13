Feature: Creating invoices
  In order to manage my invoices
  As a business owner
  I want to be able to create invoices

@api
Scenario Outline: Check labels for inline entities
  Given I am logged in as a user with the "business owner" role
  When I go to the add invoice form
  Then I should see the fieldset with the legend "<legend>"
  When I press the "<add new>" button
  Then I should see the fieldset with the legend "<add new>"
  And I should see the button "<create>"
  When I press the 'Cancel' button
  And I press the "<add existing>" button
  Then I should see the fieldset with the legend "<add existing>"
  And I should see the button "<add>"

  Examples:
  | legend   | add new         | create         | add existing         | add         |
  | Client   | Add new client  | Create client  | Add existing client  | Add client  |
  | Services | Add new service | Create service | Add existing service | Add service |
  | Products | Add new product | Create product | Add existing product | Add product |

@api
Scenario: Inline editing of a line item after adding it
  Given I am logged in as a user with the 'business owner' role
  When I go to the add invoice form
  And I press "Add new service" in the "Services" fieldset
  And I enter the following:
  | Description | A useful service |
  | Unit cost | 99.99 |
  | Quantity | 12 |
  | Tax rate | 19.50 |
  | Discount | 5 |
  And I select the radio button "months"
  And I press "Create service" in the "Add new service" fieldset
  And I press "Edit" in the "Services" fieldset
  Then I should see the following field values:
  | Description | A useful service |
  | Unit cost | 99.99 |
  | Quantity | 12 |
  | Tax rate | 19.50 |
  | Discount | 5 |
  And the radio button option "months" should be selected
