# 1、命令参数：

```bash
dd
	if=file           # 输入文件
	of=file           # 输出文件
	ibs=bytes         # 一次输入字节数(即: 块大小)
	obs=bytes         # 一次输出字节数
	bs=bytes          # 一次输入/输出字节数
	cbs=bytes         # 一次转换字节数(即：缓冲区大小)
	skip=blocks       # 从输入文件开头跳过blocks个块后开始复制
	seek=blocks       # 从输出文件开头跳过blocks个块后再开始写入
	count=blocks      # 拷贝blocks个块
	conv=key
		lcase             # 大写字符转换为小写
		ucase             # 小写字符转换为大写
		sync              # 将每个输入块填充到ibs个字节，不足部分用空（NUL）字符补齐
		fdatasync         # 完成前物理写入输出文件数据
		fsync             # 同时写入元数据
	oflag=flag
		direct            # 使用直接I/O写入数据（不使用缓存）
		dsync             # 使用同步I/O写入数据
		sync              # 同时使用同步I/O写入元数据
```

# 2、常见用法：

```bash
# 将img文件写入指定块设备（直接操作裸设备）
dd if=boot.img of=/dev/fd0 bs=1440k

# 有可能修复磁盘
dd if=/dev/sda of=/dev/sda
```

