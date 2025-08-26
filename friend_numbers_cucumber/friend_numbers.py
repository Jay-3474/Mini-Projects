def prime_check(num):
    flag = 1
    # check for factors
    for i in range(2, num):

        # If num is divisible by any number between
        # 2 and num/2, it is not prime
        if num % i == 0:
            flag = 0
            break

    if num <= 1:
        flag = 0

    if flag == 1:
        return 1
    return 0


def friend_check(num1, num2):
    if (
        ((num1 - num2) == 2 or -2)
        and (1 == prime_check(num1))
        and (1 == prime_check(num2))
    ):
        return True

    return False


# n1 = int(input())
# n2 = int(input())
# n = friend_check(n1,n2)
# if n == True:
#     print("friend numbers")
# else:
#     print("not friend numbers")
