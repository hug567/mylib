# windows中安装matplotlib：pip install matplotlib
# 运行：python test_base.py
# 2024-08-16

import matplotlib.pyplot as plt
import numpy as np

x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
y = np.array([3, 8, 7, 4, 0, 5, 2, 6, 1])

plt.plot(x,y)
plt.show()