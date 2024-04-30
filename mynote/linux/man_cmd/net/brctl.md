# 1、命令参数：

```bash
# 安装
sudo apt install bridge-utils

brctl
	-h
```

# 2、常见用法：

```bash
# 查看网桥信息
brctl show
# 查看指定网桥信息
brctl show <br0>
# 查看指定网桥mac地址表
brctl showmacs <br0>
# 查看指定网桥stp
brctl showmstp <br0>
```

- 网桥操作：

```bash
# 查看网桥及连接在网桥上的网卡
brctl show

# 查看网桥网卡信息
ifconfig / ip a / ip link show

# 显示网桥上的接口信息

```

