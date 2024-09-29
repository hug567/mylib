# define class, for other files import

class Car:

    def __init__(self, length=0, width=0, height=0):
        self.length=length
        self.width=width
        self.height=height

    def info(self):
        print("car length:", self.length)
        print("car width:", self.width)
        print("car height:", self.height)

# Inherit parent class
class PetrolCar(Car):

    def __init__(self, length=0, width=0, height=0, capacity=0):
        # call parent class constructor
        super().__init__(length, width, height)
        # subclass constructor initialization
        self.capacity = capacity

    def info(self):
        # call parent class method first
        super().info()
        print("car capacity:", self.capacity)

# Inherit parent class
class ElectricCar(Car):

    def __init__(self, length=0, width=0, height=0, electricity=0):
        # call parent class constructor
        super().__init__(length, width, height)
        # subclass constructor initialization
        self.electricity = electricity

    def info(self):
        # call parent class method first
        super().info()
        print("car electricity:", self.electricity)
