Feature: Invoices
  In order to manage my invoices
  As a business owner
  I want to be able to create new invoices

Background:
  Given I am logged in as a user with the 'business owner' role
  And client:
  | name    | email           |
  | Axemill | info@axemill.eu |

@api
Scenario: View the detail page of an invoice

  Given services:
    | description | unit cost | time unit | quantity | tax   | discount |
    | service 1   | 237.12    | weeks     | 21       | 33.33 | 40.05    |
    | service 2   | 199.95    | years     | 1        | 21    | 0        |

  Given products:
    | description | unit cost | quantity | tax   | discount |
    | product 1   | 100       | 20       | 15    | 10       |
    | product 2   | 14        | 3        | 12.5  | 7        |

  Given invoice:
    | client  | number | date     | discount | products             | services             |
    | Axemill | 15/001 | 20150223 | 12.13    | product 1, product 2 | service 1, service 2 |

  When I visit the detail page for invoice '15/001'
  Then I see the text 'Axemill'
  And I see the text '15/001'
  And I see the text 'February 23, 2015'
  And I see the text '12.13'
  And I see the text '4414.79'
  And I see the text '5567.50'
