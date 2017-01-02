# language: en
Feature: Light Switch scheduler
  In order to automatic turn lights on and off at specific times
  As a resident
  I want to be able to schedule lights to turn on/off with the Home Automation System

  Scenario Outline: A light scheduled for a specific time of the day should turn on at the scheduled time and no sooner or later
    Given light 0 is scheduled to turn "ON" at <schedule time>
    And the light 0 is "OFF"
    When the time turns <time>
    Then the light 0 should be "<state>"

    Examples:
      | schedule time | time  | state |
      | 09:00         | 08:00 | OFF   |
      | 09:00         | 08:59 | OFF   |
      | 09:00         | 09:00 | ON    |
      | 09:00         | 09:01 | OFF   |
      | 09:00         | 10:00 | OFF   |

  Scenario Outline: A light scheduled for a specific time of the day should turn off at the scheduled time and no sooner or later
    Given light 0 is scheduled to turn "OFF" at <schedule time>
    And the light 0 is "ON"
    When the time turns <time>
    Then the light 0 should be "<state>"

    Examples:
      | schedule time | time  | state |
      | 09:00         | 08:00 | ON    |
      | 09:00         | 08:59 | ON    |
      | 09:00         | 09:00 | OFF   |
      | 09:00         | 09:01 | ON    |
      | 09:00         | 10:00 | ON    |

  Scenario Outline: Multiple lights can be scheduled to turn ON/OFF.
    Given the following schedules are set:
      | schedule time | light | state |
      | 09:00         | 0     | OFF   |
      | 09:00         | 1     | ON    |
      | 09:05         | 2     | OFF   |
      | 09:05         | 3     | OFF   |

    And the following lights have state:
      | light | state |
      | 0     | ON    |
      | 1     | OFF   |
      | 2     | ON    |
      | 3     | ON    |

    When the time turns <time>
    Then the light <light 1> should be "<state 1>"
    And  the light <light 2> should be "<state 2>"
    And  the light <light 3> should be "<state 3>"
    And  the light <light 4> should be "<state 4>"

    Examples:
      | time  | light 1 | state 1 | light 2 | state 2 | light 3 | state 3 | light 4 | state 4 |
      | 08:59 | 0       | ON      | 1       | OFF     | 2       | ON      | 3       | ON      |
      | 09:00 | 0       | OFF     | 1       | ON      | 2       | ON      | 3       | ON      |
      | 09:01 | 0       | ON      | 1       | OFF     | 2       | ON      | 3       | ON      |
      | 09:05 | 0       | ON      | 1       | OFF     | 2       | OFF     | 3       | OFF     |
      | 09:06 | 0       | ON      | 1       | OFF     | 2       | ON      | 3       | ON      |


  Scenario Outline: Multiple schedules can be set for a light
    Given the following schedules are set:
      | schedule time | light | state |
      | 09:00         | 0     | OFF   |
      | 10:05         | 0     | OFF   |
      | 11:00         | 0     | OFF   |

    And the light 0 is "ON"
    When the time turns <time>
    Then the light 0 should be "<state>"

    Examples:
      | time  | state |
      | 08:59 | ON    |
      | 09:00 | OFF   |
      | 09:01 | ON    |
      | 10:04 | ON    |
      | 10:05 | OFF   |
      | 10:06 | ON    |
      | 10:59 | ON    |
      | 11:00 | OFF   |
      | 11:01 | ON    |
