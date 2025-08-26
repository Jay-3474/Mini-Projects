Feature: friend numbers checker
    As a developer
    I want to check the numbers are friends or not
    so that I can find the friend numbers

    Scenario Outline: check friend numbers
    Given a friend numbers checker
    When User provides <input1> and <input2>
    Then output should be <output>
    Examples:
        | input1 | input2 | output|
        |   3    |   5    | True  |
        |   7    |   9    | False |
        |   11   |   13   | True  |
