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
