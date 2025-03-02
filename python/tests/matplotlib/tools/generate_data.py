# 生成数据，用于测试画图脚本
# pip install numpy matplotlib
# 2025-03-02

import os
import sys
import math
import argparse
import numpy as np
import matplotlib.pyplot as plt

g_args=None

def parse_args(argv):
    global g_args
    parser = argparse.ArgumentParser(description='generate data')
    parser.add_argument('-o', '--output', type=str, default='output.txt', help='output file name')
    parser.add_argument('-l', '--length', type=int, default=1000, help='generate data length')
    g_args = parser.parse_args()

def generate_data():
    file = open(g_args.output, 'a+')
    for i in range(g_args.length):
        data0 = round(math.sin(i * 2 * math.pi / 100), 4)
        data1 = round(math.cos(i * 2 * math.pi / 100), 4)
        data2 = round(data0 + 2 * data1, 4)
        file.write(f'{data0} {data1} {data2}\n')


def main():
    parse_args(sys.argv)
    generate_data()

if __name__ == '__main__':
    main()
