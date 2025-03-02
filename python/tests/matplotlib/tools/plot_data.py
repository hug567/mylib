# 使用matplotlib画图
# 2025-03-02

import os
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt

args=None

def parse_args(argv):
    global args
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    # 原始数据文件
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
    # index: 绘制数据的索引，默认为-1，表示绘制所有数据
    #        至少指定要给索引，指定多个索引，会储存在要给列表中，args.index类型为list
    # 示例：-i 1
    #       -i 0 1 2 3 4 5
    #       -i 2 5 8
    parser.add_argument('-i', '--index', type=int, default=[-1], nargs='+', help='index of drawn data')
    # start：绘制数据图的起始下标，默认为0
    parser.add_argument('-s', '--start', type=int, default=0, help='start index of data')
    # length：绘制数据图的数据点数，默认绘制到数据结束
    parser.add_argument('-l', '--length', type=int, default=sys.maxsize, help='plot data length')

    args = parser.parse_args()

    if not args.fname or not os.path.exists(args.fname):
        print("there is no file:", args.fname)
        exit(1)
    if args.start < 0:
        args.start = 0
    print('fname:', args.fname)

def main():
    parse_args()

if __name__ == '__main__':
    main()
