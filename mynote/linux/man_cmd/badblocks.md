# 1、命令参数：

```bash
badblocks    # 检查磁盘坏块
  -s           # 检查时显示进度
  -v           # 执行时显示详细信息
  -w           # 检查时执行写入测试
  -o <file>    # 检查结果输出到文件
  -b <size>    # block大小，如4096
  -c <count>   # 每个count显示次数
```

# 2、常见用法：

```bash
badblocks -s -v /dev/sda
```



