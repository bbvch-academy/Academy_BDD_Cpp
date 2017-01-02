# language: en
Feature: Light Switch
  In order to centrally control the lights in my home
  As a resident
  I want to be able to switch on a specific light from my Home Automation System control panel

  Scenario: Turn a single light On
    Given the light 0 is "OFF"
    When I switch the light 0 "ON"
    Then the light 0 should be "ON"

  Scenario: Turn a single light Off
    Given the light 0 is "ON"
    When I switch the light 0 "OFF"
    Then the light 0 should be "OFF"

  Scenario: Turn multiple lights On/Off
    Given the following lights have state:
      | light | state |
      | 0     | OFF   |
      | 1     | OFF   |
      | 2     | ON    |
      | 3     | ON    |
      | 4     | OFF   |

    When I switch the light 0 "ON"
    When I switch the light 1 "ON"
    And I switch the light 2 "OFF"
    Then the lights should have the following states:
      | light | state |
      | 0     | ON    |
      | 1     | ON    |
      | 2     | OFF   |
      | 3     | ON    |
      | 4     | OFF   |
