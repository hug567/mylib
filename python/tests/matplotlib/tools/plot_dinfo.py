# 使用matplotlib画图
# 2025-03-02

import os
import sys
import argparse
from lib.myplot import MyPlot

g_args=None

def parse_args(argv):
    global g_args
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    # 原始数据文件
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
    # index: 绘制数据的索引，默认为-1，表示绘制所有数据
    #        至少指定1 索引，指定多个索引，会储存在要给列表中，args.index类型为list
    # 示例：-i 1
    #       -i 0 1 2 3 4 5
    #       -i 2 5 8
    parser.add_argument('-i', '--index', type=int, default=[-1], nargs='+', help='index of drawn data')
    # start：绘制数据图的起始下标，默认为0
    parser.add_argument('-s', '--start', type=int, default=0, help='start index of data')
    # length：绘制数据图的数据点数，默认绘制到数据结束
    parser.add_argument('-l', '--length', type=int, default=sys.maxsize, help='plot data length')
    # 绘制多个子图时，指定排列的行数和列数，不指定时值为None，将自动计算，如：
    #   [2, 3]：表示子图排列方式为2行3列
    parser.add_argument('-a', '--arrangement', type=int, nargs='+', help='sub plot arrangement')
    # 竖直直线
    parser.add_argument('-x', '--xlines', type=int, nargs='+', help='vertical lines')
    # 水平直线
    parser.add_argument('-y', '--ylines', type=float, nargs='+', help='horizontal lines')
    # 是否绘制在一个子图中
    parser.add_argument('-o', '--onesub', action='store_true', help='plot in one sub')

    g_args = parser.parse_args()

    if not g_args.fname or not os.path.exists(g_args.fname):
        print("there is no file:", g_args.fname)
        exit(1)
    if g_args.start < 0:
        g_args.start = 0
    print('fname:', g_args.fname)

def read_data_from_file(fname):
    all_data = []
    data_num = 0
    # udp输出的原始debug_info数据，如：
    #   data:,39.497826,39.436588,18.900000,0.000000,122.000000,31.837664, ...
    with open(fname, 'r') as file:
        first_line = file.readline().split(',')
        data_num = len(first_line) - 1

    for i in range(0, data_num):
        all_data.append([])

    with open(fname, 'r') as file:
        lines = file.readlines()
        for line in lines:
            cur_list = line.split(',')
            for i in range(0, data_num):
                all_data[i].append(float(cur_list[i + 1]))

    return all_data

def plot_data():
    data = read_data_from_file(g_args.fname)
    mplot = MyPlot()
    mplot.data = data
    mplot.index = g_args.index
    mplot.start = g_args.start
    mplot.length = g_args.length
    mplot.arrangement = g_args.arrangement
    mplot.xlines = g_args.xlines
    mplot.ylines = g_args.ylines
    mplot.onesub = g_args.onesub
    mplot.plot()

def main():
    parse_args(sys.argv)
    plot_data()

if __name__ == '__main__':
    main()
