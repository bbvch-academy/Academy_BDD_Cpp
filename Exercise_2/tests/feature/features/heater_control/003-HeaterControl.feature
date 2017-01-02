# language: en
Feature: Heater
  In order to feel comfortable
  As a resident
  I want control the room temperature centrally

  Scenario Outline: Set a temperature
    Given the current temperature is <temp>°C
    When I set the room temperature to <room_temp>°C
    Then the heater should be "<heater>"

    Examples:
      | temp | room_temp | heater |
      | 18   | 20        | ON     |
      | 21   | 20        | OFF    |
      | 20   | 20        | OFF    |

