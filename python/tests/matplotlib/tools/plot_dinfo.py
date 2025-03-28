# 使用matplotlib画图
# 2025-03-02

import os
import sys
import argparse
import numpy as np
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

# 一维高斯核，size需是奇数
def _my_gaussian_kernel(size, sigma):
    center = size // 2
    kernel = np.zeros(size) # 长度为size的np数组
    for i in range(size):
        x = i - center
        kernel[i] = np.exp(-(x * x) / (2 * sigma * sigma))
    # 归一化高斯核，确保权重总和为1
    kernel = kernel / np.sum(kernel)
    return kernel

def _my_gaussian_filter(data):
    kernel_size = 31
    sigma = 100
    kernel = _my_gaussian_kernel(kernel_size, sigma)
    print(f'kernel: {kernel}')
    filter_data = np.zeros(len(data))
    for i in range(kernel_size):
        filter_data[i] = data[i]
    for i in range(kernel_size, len(data)):
        filter_data[i] = np.sum(data[i-kernel_size:i] * kernel)

    return filter_data

def _my_average_filter(data):
    old = data[:]
    for i in range(len(data)):
        if i < 10:
            data[i] = sum(old[0:i+1]) / (i + 1)
        else:
            data[i] = sum(old[i-10:i+1]) / 10
    return data

def _my_filter(data):
    #return data
    #return _my_average_filter(data)
    #filter_data = gaussian_filter1d(data, 30)
    #print(f'type(filter_data): {type(filter_data)}')
    filter_data = _my_gaussian_filter(data)
    return list(filter_data)

# 对数据做处理
def handle_data(data_arr):
    #return data_arr
    for i in range(len(data_arr)):
        if i == 100:
            # 一维列表中元素统一减去一个固定值
            #data_arr[i] = list((np.array(data_arr[i]) + 70) / 6 + 3)
            data_arr[i] = list((np.array(data_arr[i]) - 4) / 4 + 0)
        #if i == 2:
        #    data_arr[i] = _my_filter(data_arr[i])
    return data_arr

def plot_data():
    data_arr = read_data_from_file(g_args.fname)
    data_arr = handle_data(data_arr)
    mplot = MyPlot()
    mplot.data = data_arr
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
