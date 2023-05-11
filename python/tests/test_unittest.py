#!/usr/bin/python3
################################################################################
# python练习：测试
# python版本：python 3.6.9
# 时间：2021-11-21
################################################################################
import sys
import unittest

# 普通函数
def add(a, b):
    return a + b

# 测试普通函数
class TestAdd(unittest.TestCase):
    def test_add(self):
        ans = add(1, 2)
        self.assertEqual(ans, 3)

# 普通类
class Math:
    def sub(self, a, b):
        return a - b

# 测试一个类
class TestMath(unittest.TestCase):
    def setUp(self): # setUp方法，创建当前测试用例中都可使用的实例
        self.m = Math()

    def test_sub(self):
        ans = self.m.sub(6, 2) # 使用setUp方法创建的实例
        self.assertEqual(ans, 4)

# 测试类

unittest.main()
