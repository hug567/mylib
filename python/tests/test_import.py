#!/usr/bin/python3
################################################################################
# Description: import python class
# Version: python 3.6.9
# Time: 2023-05-11
################################################################################
import sys
# import single class
from car import Car

def test_car():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    car01 = Car(100, 200, 300)
    car01.info()

def main():
    test_car()

if __name__ == '__main__':
    main()
