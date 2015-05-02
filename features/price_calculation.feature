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
