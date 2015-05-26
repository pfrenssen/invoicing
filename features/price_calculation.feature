Feature: Line item price calculation
  In order to get an overview of the cost of a line item
  As a business owner
  I want to be able to see the calculated price of a line item

Background:
  Given I am logged in as a user with the 'business owner' role

@api
Scenario Outline: The price calculation for a service should be correct
  Given service:
    | description   | unit cost   | time unit   | quantity   | tax   | discount   |
    | <description> | <unit cost> | <time unit> | <quantity> | <tax> | <discount> |
  Then the price calculation of the "<description>" line item should equal "<total>"

  Examples:
    | description | unit cost | time unit | quantity | tax   | discount | total   |
    | service 1   | 100       | hours     | 20       | 15    | 10       | 2070.00 |
    | service 2   | 14        | days      | 3        | 12.5  | 7        | 43.94   |
    | service 3   | 237.12    | weeks     | 21       | 33.33 | 40.05    | 3980.19 |
    | service 4   | 0         | months    | 0        | 0     | 0        | 0.00    |
    | service 5   | 199.95    | years     | 1        | 21    | 0        | 241.94  |

@api
Scenario Outline: The price calculation for an invoice should be correct
  Given client:
    | name    | email           |
    | Axemill | info@axemill.eu |

  Given services:
    | description   | unit cost   | time unit   | quantity   | tax   | discount |
    | service 1     | 100         | hours       | 20         | 15    | 10       |
    | service 2     | 14          | days        | 3          | 12.5  | 7        |
    | service 3     | 237.12      | weeks       | 21         | 33.33 | 40.05    |
    | service 4     | 0           | months      | 0          | 0     | 0        |
    | service 5     | 199.95      | years       | 1          | 21    | 0        |

  Given products:
    | description   | unit cost   | time unit   | quantity   | tax   | discount |
    | product 1     | 100         | hours       | 20         | 15    | 10       |
    | product 2     | 14          | days        | 3          | 12.5  | 7        |
    | product 3     | 237.12      | weeks       | 21         | 33.33 | 40.05    |
    | product 4     | 0           | months      | 0          | 0     | 0        |
    | product 5     | 199.95      | years       | 1          | 21    | 0        |

  Given invoice:
    | client   | number   | date   | discount            | products   | services   | total           |
    | <client> | <number> | <date> | <discount invoice>  | <products> | <services> | <invoice total> |
  Then the price calculation of the "<number>" invoice should equal "<invoice total>"

  Examples:
    | client   | number | date     | discount invoice | products                                              | services                                              | invoice total    |
    | Axemill  | 15/001 | 20150223 | 12,13            | product 1, product 2, product 3, product 4, product 5 | service 1, service 2, service 3, service 4, service 5 | 14209,27         |
