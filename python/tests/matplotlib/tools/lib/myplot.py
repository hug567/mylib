# 自定义绘制图形库，根据输入的数据及要求绘制曲线图
# 2025-03-05

import sys
import math
import numpy as np
import matplotlib.pyplot as plt

class MyPlot():

    def __init__(self):
        # 待绘制的数据列表，成员是多个相同长度的单列表
        self.data = []
        # index: 绘制数据的索引，默认为-1，表示绘制所有数据
        #        至少指定1个索引，index数据类型为list
        self.index = [-1]
        # 绘制数据的起始下标
        self.start = 0
        # 绘制数据的长度，最多绘制到数据结束
        self.length = sys.maxsize
        # 一个窗口中绘制多个子图时，指定排列的行数和列数，不指定时自动计算，如：
        #   [2, 3]：表示子图排列方式为2行3列
        self.arrangement = None
        # 水平/数值直线，默认不绘制，类型为list
        self.xlines = None
        self.ylines = None
        # 是否绘制在一个子图中，默认每个曲线分别绘制在不同子图中
        self.onesub = None

    # 根据要绘制的图形的数量，决定在在一个窗口中排列的行数和列数
    def __plot_arrangement_style(self, size):
        max_x = int(math.sqrt(size))
        for x in range(max_x, 1, -1):
            y = math.ceil(size / x)
            if x * (y - 1) < size:
                return [x, y]
        return [1, size]

    def plot(self):
        if self.index[0] == -1:
            self.index = np.array(range(len(self.data)))
        self.length = min(self.length, len(self.data[0]) - self.start)
        print(f'data index: {self.index}, start: {self.start}, length: {self.length}')

        if not self.arrangement:
            [x, y] = self.__plot_arrangement_style(len(self.index))
        else:
            [x, y] = self.arrangement
        print(f'sub plot arrangement: [{x}, {y}]')

        plt.figure(1)
        num = 0
        x_data = np.array(range(self.length))
        for i in self.index:
            if self.onesub:
                ax = plt.subplot(1, 1, 1)
            else:
                ax = plt.subplot(x, y, num + 1)
            plt.sca(ax)
            y_data = self.data[i][self.start:self.start+self.length]

            # 对数据作处理后再绘制
            #if i == 9:
            #    y_data = [(x - 129) * 20 / 2.4 for x in y_data]

            # 打印猫符合锁定条件的波峰宽度
            #count = 0
            #for i in range(len(y_data)):
            #    if y_data[i] > 2:
            #        count += 1
            #    elif count > 0:
            #        print(f'lock count: {count}')
            #        count = 0
            #    if count > 0 and i == len(y_data) - 1:
            #        print(f'last lock count: {count}')

            y_max = max(y_data)
            y_max_index = y_data.index(y_max)
            y_min = min(y_data)
            y_min_index = y_data.index(y_min)
            y_middle = round((y_max + y_min) / 2, 3)
            print(f'i: {i}, y_max({y_max_index}): {y_max}, y_min({y_min_index}): {y_min}, y_middle: {y_middle}')
            plt.plot(x_data, y_data, label='y_data')
            if self.xlines:
                for xp in self.xlines:
                    plt.axvline(x=xp, color='r', linestyle='-.')
            if self.ylines:
                for yp in self.ylines:
                    plt.axhline(y=yp, color='r', linestyle='-.')
            # 显示网格
            plt.grid(True)
            num += 1

        # 绘图窗口最大化
        manager = plt.get_current_fig_manager()
        manager.window.showMaximized()
        # 显示绘图窗口
        plt.show()
