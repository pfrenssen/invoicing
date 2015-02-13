Feature: Creating invoices
  In order to manage my invoices
  As a business owner
  I want to be able to create invoices

@api
Scenario Outline: Check labels for inline entities
  Given I am logged in as a user with the "business owner" role
  When I go to the add invoice form
  Then I should see a fieldset with the legend "<legend>"
  When I press the "<add new>" button
  Then I should see a fieldset with the legend "<add new>"
  And I should see a button with label "<create>"
  When I press the 'Cancel' button
  And I press the "<add existing>" button
  Then I should see a fieldset with the legend "<add existing>"
  And I should see a button with label "<add>"

  Examples:
  | legend   | add new         | create         | add existing         | add         |
  | Client   | Add new client  | Create client  | Add existing client  | Add client  |
  | Services | Add new service | Create service | Add existing service | Add service |
  | Products | Add new product | Create product | Add existing product | Add product |
