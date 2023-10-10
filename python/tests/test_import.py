#!/usr/bin/python3
################################################################################
# Description: import python class
# Version: python 3.6.9
# Time: 2023-05-11
################################################################################
import sys
# import single class
from car import Car
# import multiple classes
from car import PetrolCar, ElectricCar

def test_car():
    print(sys._getframe().f_code.co_name, ": -------------------------", sep='')
    print("car: ----------------")
    car01 = Car(100, 200, 300)
    car01.info()

    print("petro car: ----------")
    petrol = PetrolCar(100, 200, 300, 400)
    petrol.info()

    print("electric car: ----------")
    electric = ElectricCar(100, 200, 300, 500)
    electric.info()

def main():
    test_car()

if __name__ == '__main__':
    main()
