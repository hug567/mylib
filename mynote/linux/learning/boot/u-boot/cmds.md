## 1、常用命令：

### 常用：

```bash
# 查看板子硬件信息
bdinfo
# 查看uImage信息
iminfo  0x60003000
# 查看内存二进制值
md 0x60003000
```

### boot：

```bash
# u-boot 2014中为tftp
tftp
# 通过网络从tftp服务器下载文件到内存
tftpboot 0x60003000 zImage

# 启动内存中的内核镜像
bootm 0x60003000 0x62000000 0x61000000

# 启动内存中未压缩的arm64镜像
booti 0x40003000 0x44000000 0x45000000
```

### env：

```bash
# 打印所有环境变量的值
printenv
# 打印制定环境变量的值
printenv <var>

# 保存环境变量至永久存储设备中
saveenv

# 设置环境变量的值
setenv <var> <value>
# 删除环境变量
setenv <var>
# 强制设置环境变量的值
setenv -f <var> <value>
# 强制删除环境变量
setenv -f <var>
```

### fat：

```bash
# 查看指定设备的fat文件系统信息
fatinfo mmc 0
# 查看指定fat文件系统中的文件
fatls mmc 0
fatls mmc 0 <dir>
# 查看fat文件系统类型
fstype mmc 0
# 读取文件到内存指定地址
fatload mmc 0 0x00000000 /success/BOOT.BIN
# 把内存中文件写入mmc设备
fatwrite mmc 0 00000000 image.ub 0x90caa8
```

### help：

```bash
# 查看所有命令
help / ?
# 查看制定命令帮助
help <cmd>
```

### mmc：

```bash
# 查看mmc设备信息
mmc info
# 列出mmc分区
mmc part
# mmc设备读写
mmc read/write/erase
```

### nand：

```bash
nand info
nand read/wirte/erase.chip/bad
```

### net：

```bash
# ping IP地址
ping 192.168.0.1
```




