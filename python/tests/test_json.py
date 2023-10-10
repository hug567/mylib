#!/usr/bin/python3
################################################################################
# python练习：json文件
# python版本：python 3.6.9
# 时间：2021-11-21
################################################################################
import os
import sys
import json

nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
fname = 'nums.json'
# 写入json文件
with open(fname, 'w') as fobj:
    json.dump(nums, fobj)

# 读取json文件
with open(fname) as fobj:
    num2 = json.load(fobj)
    print(num2)

# 删除文件
os.remove(fname)
