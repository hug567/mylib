# 1、命令参数：

```bash
minicom
	-h                          # 查看帮助
	-D <dev>                    # 指定设备
```

# 2、常见用法：

```bash
# 打开串口
sudo minicom -D /dev/ttyUSB0
# 推出minicom
Ctrl+A -> X -> Enter
# 查看命令
Ctrl+A -> Z
# 开关时间戳，多次按显示不同类型时间戳
Ctrl+A -> N
```

