# 绘制cpu1程序上传的debug_info_t中的数据
# 2024-08-16

import matplotlib.pyplot as plt
import numpy as np
import os
import sys
import argparse

args=None

def parse_args(argv):
    global args
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
    args = parser.parse_args()

    if not os.path.exists(args.fname):
        print("there is no file:", args.fname)
        exit(1)
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

def dat_plot_dinfo_index():
    index_col = []
    f = open(args.fname)
    lines = f.readlines()
    for line in lines:
        index = dat_get_line_data_by_index(line, 14)
        index_col.append(index)
    print("index_col size:", len(index_col))

    not_lost_count = 1
    for i in range(len(index_col) - 1, 0, -1):
        index_col[i] = index_col[i] - index_col[i - 1]
        if index_col[i] != 1:
            if (index_col[i] > 100):
                print("index add is larger then 100: ", index_col[i], ", i:", i)
                index_col[i] = -1
        else:
            not_lost_count = not_lost_count + 1
    index_col[0] = 1.0
    print("not_lost_count:", not_lost_count)

    x = np.array(range(len(index_col)))
    y = np.array(index_col)
    plt.plot(x, y)
    plt.show()

# 绘制IMU姿态信息：yaw、pitch、roll
def dat_plot_dinfo_attitude():
    yaw_col = []
    pitch_col = []
    roll_col = []
    f = open(args.fname)
    lines = f.readlines()
    for line in lines:
        yaw_col.append(dat_get_line_data_by_index(line, 9))
        pitch_col.append(dat_get_line_data_by_index(line, 8))
        roll_col.append(dat_get_line_data_by_index(line, 7))
    print("data col size:", len(yaw_col))

    x = np.array(range(len(yaw_col)))
    y1 = np.array(yaw_col)
    y2 = np.array(pitch_col)
    y3 = np.array(roll_col)

    plt.figure(1)
    # 一个窗口中画3个图，3行1列
    ax1 = plt.subplot(3, 1, 1) # 索引为1的图
    ax2 = plt.subplot(3, 1, 2) # 索引为2的图
    ax3 = plt.subplot(3, 1, 3) # 索引为3的图

    plt.sca(ax1) # 选择图形窗口
    plt.plot(x, y1) # 绘制曲线
    plt.sca(ax2) # 选择图形窗口
    plt.plot(x, y2) # 绘制曲线
    plt.sca(ax3) # 选择图形窗口
    plt.plot(x, y3) # 绘制曲线

    plt.show()

def main():
    parse_args(sys.argv)
    if is_dat_file():
        print("supplied file is a dat file")
        dat_plot_dinfo_index()
        dat_plot_dinfo_attitude()
    if is_csv_file():
        print("supplied file is a dat file")

if __name__ == '__main__':
    main()
