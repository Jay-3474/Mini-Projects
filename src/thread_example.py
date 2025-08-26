from multiprocessing.connection import wait
from threading import Thread
from time import sleep


def th1():
    print("Hi 1....")
    sleep(5)
    print("completed...")


def th2():
    print("Hi 2...")


thread_1 = Thread(target=th1)
thread_2 = Thread(target=th2)

thread_1.start()
thread_2.start()
