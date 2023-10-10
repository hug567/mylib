#!/usr/bin/python3
################################################################################
# python练习：if语句
# python版本：python 3.6.9
# 时间：2021-11-16
################################################################################
import sys

# 真: True
# 假: False

# 简单if语句
subjects = ["math", "english"]
for sub in subjects:
    if sub == "math": # 字符串比较相等
        print(sub.title())
    elif sub != "math": # 字符串比较不相等
        print(sub.upper())
    else:
        print("xxx")
