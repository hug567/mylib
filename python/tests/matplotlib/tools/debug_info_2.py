# 绘制cpu1程序上传的debug_info_t中的数据
# 2025-02-28

import os
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter
from scipy.ndimage import gaussian_filter1d

args=None
g_max_size = 16

def parse_args(argv):
    global args
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    # 原始数据文件
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
    # index: 绘制数据的索引，默认为-1，表示绘制所有数据
    #        至少指定1个索引，指定多个索引，会储存在要给列表中，args.index类型为list
    # 示例：-i 1
    #       -i 0 1 2 3 4 5
    #       -i 2 5 8
    parser.add_argument('-i', '--index', type=int, default=[-1], nargs='+', help='index of drawn data')
    # start：绘制数据图的起始下标，默认为0
    parser.add_argument('-s', '--start', type=int, default=0, help='start index of data')
    # length：绘制数据图的数据点数，默认绘制到数据结束
    parser.add_argument('-l', '--length', type=int, default=100000000, help='length of data')

    args = parser.parse_args()

    if not args.fname or not os.path.exists(args.fname):
        print("there is no file:", args.fname)
        exit(1)
    if args.start < 0:
        args.start = 0
    print('fname:', args.fname)

def is_dat_file():
    fname = args.fname
    sub = os.path.splitext(fname)[-1][1:]
    if sub == "dat":
        return True
    return False

def is_csv_file():
    fname = args.fname
    sub = os.path.splitext(fname)[-1][1:]
    if sub == "csv":
        return True
    return False

def dat_get_line_data_by_index(line, index):
    datas = line.split(',')
    return float(datas[index + 1])

# 根据要绘制的图形的数量，决定在在一个窗口中排列的行数和列数
def plot_arrangement_style(size):
    if size < 1:
        size = 1
    if size > g_max_size:
        size = g_max_size
    arrange = [
        [1, 1], # 0
        [1, 2],
        [2, 2],
        [2, 2],
        [2, 3],
        [2, 3],
        [3, 3],
        [3, 3],
        [3, 3],
        [3, 4],
        [3, 4],
        [3, 4],
        [4, 4],
        [4, 4],
        [4, 4],
        [4, 4], # 15
    ]
    return arrange[size - 1]

def dat_parse_all_data():
    all_data = []
    for i in range(0, g_max_size):
        all_data.append([])

    f = open(args.fname)
    lines = f.readlines()
    for line in lines:
        for i in range(0, g_max_size):
            data = dat_get_line_data_by_index(line, i)
            all_data[i].append(data)

    return all_data

def gaussian_kernel(size, sigma):
    center = size // 2
    kernel = np.zeros(size)
    for i in range(size):
        x = i - center
        kernel[i] = np.exp(-(x ** 2) / (2 * sigma ** 2))
    # 归一化高斯核，确保权重总和为 1
    kernel = kernel / np.sum(kernel)
    return kernel

def gaussian_filter_manual(data, window_size, sigma):
    kernel = gaussian_kernel(window_size, sigma)
    data_length = len(data)
    padded_data = np.pad(data, (window_size // 2, window_size // 2), mode='edge')
    filtered_data = np.zeros(data_length)
    for i in range(data_length):
        if i < window_size:
            filtered_data[i] = data[i]
        else:
            #filtered_data[i] = np.sum(padded_data[i:i + window_size] * kernel)
            filtered_data[i] = np.sum(padded_data[i - window_size:i] * kernel)
    return filtered_data

# 一阶高斯滤波实现
def my_gausian_filter(data):
    return gaussian_filter_manual(data, 100, 30)

# 对如snr的数据进行滤波：
def y_data_filter(data):
    #window_size = 100
    #poly_order = 5
    #smoothed_data = savgol_filter(data, window_size, poly_order)

    #smoothed_data = gaussian_filter1d(data, sigma=30)
    smoothed_data = my_gausian_filter(data)

    return smoothed_data

def limit_max_change_ratio(data):
    filtered_data = []
    filtered_data.append(data[0])
    last = data[0]
    for i in range(1, len(data)):
        cur = data[i]
        new = data[i]
        #if abs(cur - last) > 0.1:
        #    new = (cur + last) / 2
        new = (cur + last) / 2
        filtered_data.append(new)
        last = new
    return filtered_data

def dat_plot_dinfo():
    size = len(args.index)
    index_list = args.index
    if args.index[0] < 0:
        size = g_max_size
        index_list = range(0, size)
    [x, y] = plot_arrangement_style(size)
    print(f'plot arrangement x = {x}, y = {y}')

    all_data = dat_parse_all_data()
    start = args.start
    length = min(args.length, len(all_data[0]) - start)

    plt.figure(1)
    x_data = np.array(range(length))
    num = 0
    for i in index_list:
        print(f'will plot index {i} data in pos {num}, start: {start}, length: {length}')
        ax = plt.subplot(x, y, num + 1)
        num = num + 1
        plt.sca(ax)
        y_data = all_data[i][start:start+length]
        #smoothed_data1 = y_data_filter(y_data)
        #smoothed_data2 = y_data_filter(smoothed_data1)
        #smoothed_data3 = y_data_filter(smoothed_data2)
        #plt.plot(x_data, y_data, smoothed_data1, smoothed_data2, smoothed_data3)
        plt.plot(x_data, y_data, label='y_data')
        #plt.plot(x_data, smoothed_data1, label='smoothed_data1')
        #plt.plot(x_data, smoothed_data2, label='smoothed_data2')
        #plt.plot(x_data, smoothed_data3, label='smoothed_data3')

        #no_repeat = []
        #no_repeat.append(y_data[0])
        #for i in range(1, len(y_data)):
        #    if y_data[i] != y_data[i - 1]:
        #        no_repeat.append(y_data[i])
        #plt.plot(range(len(no_repeat)), no_repeat, label='y_data')

        #diff = []
        #diff.append(0)
        #for i in range(1, len(y_data)):
        #    diff.append(abs(y_data[i] - y_data[i - 1]))
        #plt.plot(x_data, diff, label='diff')
        #plt.plot(x_data, limit_max_change_ratio(y_data), label='limit max change ratio')

        plt.legend()
        # 显示网格
        plt.grid(True)

    # 绘图窗口最大化
    manager = plt.get_current_fig_manager()
    manager.window.showMaximized()
    # 显示绘图窗口
    plt.show()

def main():
    parse_args(sys.argv)
    if is_dat_file():
        print("supplied file is a dat file")
        dat_plot_dinfo()
    elif is_csv_file():
        print("supplied file is a dat file")
    else:
        dat_plot_dinfo()

if __name__ == '__main__':
    main()
