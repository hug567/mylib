## 1、常用命令：

### 1)、boot相关：

```bash
# 查看所有命令
help / ?
# 查看指定命令帮助
help <cmd>

setenv
saveenv
printenv
tftp
tftpboot
ping
bootm

# 查看板子硬件信息
bdinfo
# 查看uImage信息
iminfo  0x60003000
# 查看内存二进制值
md 0x60003000
```

### 2）、mmc：

```bash
# 查看mmc设备信息
mmc info
```

### 3）、fat：

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



