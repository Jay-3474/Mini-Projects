*** Settings ***
Documentation    A calc code for practice
...    keywords are imported from calc file

Library    calc.py


*** Test Cases ***
Addition
    ${data}    addition    5    4
    Log    total = ${data}
    Should Be Equal    ${data}    ${9}

Multipliication
    ${data}    multiplication    5    4
    Log    total = ${data}
    Should Be Equal    ${data}    ${20}
