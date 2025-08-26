from behave import given, when, then
from friend_numbers import *

_output = ""


@given("a friend numbers checker")
def methodOne(context):
    print("c1 - Launching the App")
    pass


@when("User provides {input1} and {input2}")
def methodTwo(context, input1: int, input2: int):
    print("c2 - user inputs {}, {}".format(input1, input2))
    _output = friend_check(int(input1), int(input2))


@then("output should be {output}")
def methodTree(context, output):
    print("c3 - output {}".format(output))
    if output == _output:
        pass
