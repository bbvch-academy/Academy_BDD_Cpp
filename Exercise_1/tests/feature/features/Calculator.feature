# language: en
Feature: Cucumber-cpp Academy Exercise
  As a C++ developer with first time contact with Cucumber-cpp
  I want to implement all kind of cucumber steps without interaction to other code
  In order to learn how to define cucumber steps in C++


Scenario: Simple Steps
  Given the numbers 6 and 7
  When this numbers are multiplied
  Then the result should be 42

Scenario Outline: Examples
  Given the numbers <number 1> and <number 2>
  When this numbers are added
  Then the result should be <result>

Examples:
  | number 1  | number 2  | result  |
  |     4     |     25    |    29   |
  |   109     |     11    |   120   |
  |   600     |     66    |   666   |
  |     0     |      0    |     0   |
  |   -20     |     25    |     5   |
  |  -100     |    -25    |   -125  |

Scenario: Input Table
  Given the following numbers:
    | number | 
    |    23  |
    |    45  |
    |    34  |
    |   100  |
    
  When each number is multiplied by 2
  Then the results should be the following:
    | result | 
    |    46  |
    |    90  |
    |    68  |
    |   200  |

Scenario: String Input
  Given the following text
    """
    Then the Queen left off, quite out of breath, and said to Alice, 
    'Have you seen the Mock Turtle yet?'
    'No,' said Alice. 'I don't even know what a Mock Turtle is.'
    'It's the thing Mock Turtle Soup is made from,' said the Queen.
    'I never saw one, or heard of one,' said Alice.
    'Come on, then,' said the Queen, 'and he shall tell you his history,' 
    """
  When the word Mock are counted in the text
  Then the count should be 3
  
  
