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
    size = 3
    cycle = 2400
    for i in range(size):
        data.append([])

    for i in range(600):
        # AngleDes以300个数据点的周期按正弦规律变化
        T = 300
        num = 0.025 * math.sin(i * 2 * math.pi / 300) + 0.95
        #num = math.sin(i * 2 * math.pi / T)
        data[0].append(num)

        T = cycle # snr变化周期为cycle，取顶点两边各75个点的数据
        if i < 75:
            num = math.cos(i * 2 * math.pi / T)
            data[1].append(num)
        elif i < 150:
            num = math.cos((i * 2 * math.pi / T) - (math.pi / 8))
            data[1].append(num)
        else:
            data[1].append(data[1][i - 150])

        T = cycle
        offset = 25 # 偏移点数，正弦扫描中心点未对准卫星
        if i < 75:
            #num = math.sin((i * 2 * math.pi / cycle) + (math.pi / 2 + (offset * 2 * math.pi / cycle)))
            num = math.cos((i * 2 * math.pi / T) - math.pi / 48)
            data[2].append(num)
        elif i < 150:
            #num = math.sin((i * 2 * math.pi / cycle) + (math.pi * 3 / 8 + (offset * 2 * math.pi / cycle)) - 7 * math.pi / 24)
            a = 75
            num = math.cos((2 * math.pi * (2 * a - i)) / T - math.pi / 48)
            data[2].append(num)
        else:
            data[2].append(data[2][i - 150])

        #if i < 38:
        #elif i < 114:
        #elif i < 190:
        #elif i < 266:
        #elif i < 342:
        #elif i < 418:
        #elif:
        #num = math.cos(i * 2 * math.pi * 2 / cycle)
        #data[1].append(num)

        #num = math.cos((i + 10) * 2 * math.pi * 2 / cycle)
        #data[2].append(num)

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
            [75, 'r'],
            [225, 'r'],
            [100, 'b'],
            [200, 'b'],
            [60, 'g'],
            [240, 'g'],
            [300, 'r'],
            [600, 'r'],
            ]
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
