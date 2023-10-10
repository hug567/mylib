#!/usr/bin/python3
################################################################################
# python练习：异常
# python版本：python 3.6.9
# 时间：2021-11-21
################################################################################
import sys

# ZeroDivisionError异常
try:
    print(5 / 0)
except ZeroDivisionError:
    print('zero can not be divisior')

# try成功执行
try:
    answer = 2 / 5
except ZeroDivisionError:
    print('zero can not be divisior')
else: # try执行后执行else中语句
    print("answer: ", answer, sep='')

# FileNotFoundError异常
fname = 'xxx.txt'
try:
    with open(fname) as fobj:
        contents = fobj.read()
except FileNotFoundError:
    print("file ", fname, " does not exist", sep='')

# 发生异常是不做任何处理
fname = 'xxx.txt'
try:
    with open(fname) as fobj:
        contents = fobj.read()
except FileNotFoundError:
    pass
else:
    print(contents)

