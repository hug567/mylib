################################################################################
# python练习：类
# python版本：python 3.6.9
# 时间：2021-11-20
################################################################################
import sys

# 创建类
class Book(): # 类名使用驼峰命名法

    def __init__(self, name, price): # 构造函数
        self.name = name
        self.price = price
        self.pages = 0 # 属性指定默认值

    def get_name(self):
        return self.name

    def get_price(self):
        return self.price

    def set_name(self, name):
        self.name = name

    def set_price(self, price):
        self.price = price

# 创建类的实例
book1 = Book('math', 100)
# 访问属性
print("book name: ", book1.name, sep='')
print("book price: ", book1.price, sep='')
print("book pages: ", book1.pages, sep='')
# 直接修改属性值
book1.pages = 120
print("book pages: ", book1.pages, sep='')
# 调用方法
book1.set_name('english')
book1.set_price(200)
print("book name: ", book1.get_name(), sep='')
print("book price: ", book1.get_price(), sep='')

# 继承
class ElectricBook(Book):

    def __init__(self, name, price, size):
        supre().__init__(name, price) # 调用父类构造函数
        self.size = size
