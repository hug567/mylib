#!/bin/bash
# 获取指定分辨率所需参数
#cvt 1600 900
# 查看显示设备信息
#xrandr
# 创建新的显示模式
xrandr --newmode "1600x900_60.00"  118.25  1600 1696 1856 2112  900 903 908 934 -hsync +vsync
# 添加新的显示模式
sudo xrandr --addmoe Virtual1 "1600x900_60.00"
# 使用新添加的显示模式
xrandr --output Virtual1 --mode 1600x900_60.00
