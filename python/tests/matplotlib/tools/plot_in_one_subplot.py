# 绘制AngleDes和snr，计算两者之间的延迟
# 原始数据文件需只有两列，已空格分割，第一列是AngleDes，第二列是snr
# 2025-03-01

import os
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter
from scipy.ndimage import gaussian_filter1d

args=None

def parse_args(argv):
    global args
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    # 原始数据文件
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
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
    print(f'fname: {args.fname}, start: {args.start}')

def dat_get_line_data_by_index(line, index):
    datas = line.split(',')
    return float(datas[index + 1])

def read_data_from_file(fname):
    all_data = []
    data_num = 0
    with open(fname, 'r') as file:
        first_line = file.readline().split()
        data_num = len(first_line)

    for i in range(0, data_num):
        all_data.append([])

    f = open(fname)
    lines = f.readlines()
    for line in lines:
        for i in range(0, data_num):
            data = float(line.split()[i])
            all_data[i].append(data)

    return all_data

def plot_in_one_subplot(fname, start, length):
    all_data = read_data_from_file(fname)
    show_length = min(length, len(all_data[0]) - start)
    print(f'show_length: {show_length}')

    plt.figure(1)
    x_data = np.array(range(show_length))
    data_num = len(all_data)
    ax = plt.subplot(1, 1, 1)
    plt.sca(ax)
    for i in range(0, data_num):
        plt.plot(x_data, all_data[i][start:start+show_length])

    des_min = min(all_data[0][start:start+show_length])
    des_max = max(all_data[0][start:start+show_length])
    des_middle = (des_max - des_min) / 2 + des_min
    print(f'AngleDes max: {des_max}, min: {des_min}, diff: {des_max-des_min}, middle: {des_middle}')

    #plt.legend()
    # 显示一条水平曲线
    plt.axhline(y=des_middle, color='g', linestyle='--')
    # 显示一条竖直曲线
    plt.axvline(x=1460, color='r', linestyle='-.')
    plt.axvline(x=1770, color='b', linestyle='-.')
    # 显示文本
    plt.text(1340, 32.5, 'A', fontsize=15, color='red')
    plt.text(1800, 19.5, 'B', fontsize=15, color='red')
    # 显示实心圆点
    plt.scatter(1460, 36.73,  color='red', marker='o', zorder=10)
    plt.scatter(1770, 19,  color='red', marker='o', zorder=10)
    # 显示网格
    plt.grid(True)
    # 绘图窗口最大化
    #manager = plt.get_current_fig_manager()
    #manager.window.showMaximized()
    # 显示绘图窗口
    plt.show()

def main():
    parse_args(sys.argv)
    plot_in_one_subplot(args.fname, args.start, args.length)

if __name__ == '__main__':
    main()
