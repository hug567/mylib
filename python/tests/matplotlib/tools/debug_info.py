# 绘制cpu1程序上传的debug_info_t中的数据
# 2024-08-16

import matplotlib.pyplot as plt
import numpy as np

def test_base():
    x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
    y = np.array([3, 8, 7, 4, 0, 5, 2, 6, 1])
    plt.plot(x,y)
    plt.show()

def main():
    test_base()

if __name__ == '__main__':
    main()
