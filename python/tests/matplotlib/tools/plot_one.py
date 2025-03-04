# 文本文件中只有一列数据，绘制其曲线
# 2025-03-01

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

    if not args.fname or not os.path.exists(args.fname):
        print("there is no file:", args.fname)
        exit(1)
    print('fname:', args.fname)

def read_data_from_file(fname):
    data = []
    file = open(fname)
    lines = file.readlines()
    for line in lines:
        data.append(float(line))
    return data

def plot_one_line(data):
    x_data = range(0, len(data))
    ax = plt.subplot(1, 1, 1)
    plt.sca(ax)
    plt.plot(x_data, data, label='data')
    plt.legend()
    plt.grid(True)
    plt.show()

def main():
    parse_args(sys.argv)

    data = read_data_from_file(args.fname)
    plot_one_line(data)

if __name__ == '__main__':
    main()
