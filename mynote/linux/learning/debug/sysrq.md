# 1、常用命令：

- 注：结果打印在串口(console)，ssh连接看不见，可以使用dmesg查看；

```bash
# 使能所有sysrq
echo 1 > /proc/sys/kernel/sysrq

# 显示内存信息
echo m > /proc/sysrq-trigger; dmesg | tail -n 35
# 打印所有线程状态信息
echo t > /proc/sysrq-trigger
# 打印所有活动CPU的调用栈
echo l > /proc/sysrq-trigger
# 重启机器
echo b > /proc/sysrq-trigger
```
