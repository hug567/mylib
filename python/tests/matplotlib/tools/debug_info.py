# 绘制cpu1程序上传的debug_info_t中的数据
# 2024-08-16

import matplotlib.pyplot as plt
import numpy as np
import os
import argparse

def get_line_data_by_index(line, index):
    datas = line.split(',')
    return float(datas[index + 1])

def main():
    parser = argparse.ArgumentParser(description='Plot debug_info_t data')
    parser.add_argument('-f', '--fname', type=str, help='specify data file')
    args = parser.parse_args()

    if not os.path.exists(args.fname):
        print("there is no file:", args.fname)
        return
    print('fname:', args.fname)

    index_col = []
    f = open(args.fname)
    lines = f.readlines()
    for line in lines:
        index = get_line_data_by_index(line, 14)
        index_col.append(index)
    print("index_col size:", len(index_col))

    not_lost_count = 1
    for i in range(len(index_col) - 1, 0, -1):
        index_col[i] = index_col[i] - index_col[i - 1]
        if index_col[i] != 1:
            print("index add is not 1: ", index_col[i], "i:", i)
        else:
            not_lost_count = not_lost_count + 1
    index_col[0] = 1.0
    print("not_lost_count:", not_lost_count)

    x = np.array(range(len(index_col)))
    y = np.array(index_col)
    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
