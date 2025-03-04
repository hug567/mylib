# 卡尔曼滤波算法对snr做无延迟滤波
# 2025-03-03

import os
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import filtfilt,butter,savgol_filter

g_args=None

def parse_args(argv):
    global g_args
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
    # start：绘制数据图的起始下标，默认为0
    parser.add_argument('-s', '--start', type=int, default=0, help='start index of data')
    # length：绘制数据图的数据点数，默认绘制到数据结束
    parser.add_argument('-l', '--length', type=int, default=sys.maxsize, help='length of data')
    g_args = parser.parse_args()

    if not g_args.fname or not os.path.exists(g_args.fname):
        print("there is no file:", g_args.fname)
        exit(1)
    if g_args.start < 0:
        g_args.start = 0
    print('fname:', g_args.fname)

def read_data_from_file(fname):
    data = []
    file = open(fname)
    lines = file.readlines()
    for line in lines:
        data.append(float(line))
    return data

# 卡尔曼滤波：无延迟滤波算法
def kalman_filter(data):
    x_est = 0 # 估计状态初始值
    P_est = 1 # 估计误差协方差初始值
    Q = 1e-3 # 过程噪声协方差
    R = 3 # 测量噪声协方差
    x_filtered = []

    for z in data:
        x_pred = x_est
        P_pred = P_est + Q
        K = P_pred / (P_pred + R)
        x_est = x_pred + K * (z - x_pred)
        P_est = (1 - K) * P_pred
        x_filtered.append(x_est)

    return x_filtered

# 双向滤波
def forward_backward_filter(data):
    b, a = butter(10, 0.1, btype='low', analog=False)
    filter_data = filtfilt(b, a, data)
    return filter_data

# Savitzky-Golay滤波
def savitzky_golay_filter(data):
    return savgol_filter(data, window_length=100, polyorder=3)

def max_change_rate_filter(data):
    filter_data = []
    filter_data.append(data[0])
    last = data[0]
    for i in range(1, len(data)):
        cur = data[i]
        diff = cur - last
        if abs(diff) > 0.2:
            #cur = (cur + last) / 2
            if cur > last:
                cur = last + 0.2
            else:
                cur = last - 0.2
        filter_data.append(cur)
        last = cur
    return filter_data

def plot_one_line(data):
    start = g_args.start
    show_len = min(g_args.length, len(data) - start)
    if show_len <= 0:
        print(f'show_len is too small: {show_len}')
        exit(1)
    x_data = range(0, show_len)
    ax = plt.subplot(1, 1, 1)
    plt.sca(ax)
    show_data = data[start:start+show_len]
    filter_data = kalman_filter(show_data)
    #fb_filter_data = forward_backward_filter(show_data)
    plt.plot(x_data, show_data, label='original data')
    #plt.plot(x_data, filter_data, label='kalman filter')
    #plt.plot(x_data, forward_backward_filter(show_data), label='forward backward filter')
    #plt.plot(x_data, savitzky_golay_filter(show_data), label='forward backward filter')
    plt.plot(x_data, max_change_rate_filter(show_data), label='max change data')
    #plt.legend()

    # 计算前后两个数据的变化差值
    diff_data = []
    diff_data.append(0)
    for i in range(1, len(show_data)):
        diff_data.append(abs(show_data[i] - show_data[i - 1]))

    plt.plot(x_data, diff_data, label='diff data')

    # 显示网格
    plt.grid(True)
    # 绘图窗口最大化
    manager = plt.get_current_fig_manager()
    manager.window.showMaximized()
    plt.show()

def main():
    parse_args(sys.argv)

    data = read_data_from_file(g_args.fname)
    plot_one_line(data)

if __name__ == '__main__':
    main()
