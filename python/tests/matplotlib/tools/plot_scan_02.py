# 圆锥扫描工作方式
# 2025-03-11

import os
import sys
import math
import numpy as np
import matplotlib.pyplot as plt

args=None

def generate_data():
    data = []
    size = 3
    cycle = 300
    for i in range(size):
        data.append([])

    for i in range(2*cycle):
        num = math.sin(i * 2 * math.pi / cycle)
        data[0].append(num)

        num = math.cos(i * 2 * math.pi * 2 / cycle)
        data[1].append(num)

        num = math.cos((i + 10) * 2 * math.pi * 2 / cycle)
        data[2].append(num)

    return data

def generate_data2():
    data = []
    size = 10
    cycle = 2400
    for i in range(size):
        data.append([])

    for i in range(cycle):
        T = cycle
        num = math.sin(i * (2 * math.pi / T))
        data[0].append(num)

        T = cycle / 2
        num = math.cos(i * (2 * math.pi / T))
        data[1].append(num)

        T = cycle / 2
        num = math.cos(i * (2 * math.pi / T) + 100 * (2 * math.pi / T))
        data[2].append(num)

        T = cycle / 2
        num = math.cos(i * (2 * math.pi / T) - 150 * (2 * math.pi / T))
        data[3].append(num)

    return data

def plot_line(data):
    x_len = len(data[0])
    x_data = range(0, x_len)
    ax = plt.subplot(1, 1, 1)
    plt.sca(ax)
    for i in range(len(data)):
        if len(data[i]) == x_len:
            plt.plot(x_data, data[i], label=str(i))

    xlines = [
            #[80, 'r'],
            #[230, 'r'],
            [100, 'b'],
            [200, 'b'],
            [60, 'g'],
            [240, 'g'],
            [300, 'r'],
            [600, 'r'],
            ]
    xlines = None
    ylines = None
    if xlines:
        for xp in xlines:
            plt.axvline(x=xp[0], color=xp[1], linestyle=':', linewidth=2)
    if ylines:
        for yp in ylines:
            plt.axhline(y=yp, color='r', linestyle='.', size=1)

    #points = [
    #        [100, -0.1, 'r'],
    #        [200, -0.8, 'r'],
    #        [80, -0.8, 'g'],
    #        [230, -0.8, 'g'],
    #        [100, -0.5, 'b'],
    #        [200, -0.5, 'b'],
    #        ]
    #if points:
    #    for p in points:
    #        plt.scatter(p[0], p[1], marker='o', color=p[2], zorder=10)

    plt.legend()
    plt.grid(True)

    backend = plt.get_backend()
    print(f'type(backend): {type(backend)}, backend: {backend}')
    # 绘图窗口最大化
    if backend == 'qtagg':
        print(f'backend is qtagg')
        manager = plt.get_current_fig_manager()
        manager.window.showMaximized()

    plt.show()

def main():
    data = generate_data2()
    plot_line(data)

if __name__ == '__main__':
    main()
