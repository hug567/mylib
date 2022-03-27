## 1、powershell

```shell
echo $pshome                     # 查看powershell home目录
echo $profile                    # 查看powershell配置文件
test-path $profile               # 测试配置文件是否存在
```

## 2、Linux挂载Windows目录：

```shell
# 1. Windows目录设置共享:
文件夹右键 -> 属性 -> 共享 -> ......

# 2. Linux查看当前用户gid与uid:
id

# 3. Linux挂载Windows目录:
sudo mount -t cifs -o username=Administrator,password=****,gid=1000,uid=1000 //192.168.1.26/share ~/share

# 4. 卸载目录:
sudo umount ~/share
```

## 3、Windows挂载linux目录：

```shell
Ubuntu使能NFS：
	1. 安装NFS server：sudo apt install rpcbind nfs-kernel-server
	2. 查看共享目录：showmount -e
	3. 添加共享目录：sudo vim /etc/exports
	4. 重启NFS：sudo service protmap restart
	                 sudo service nfs-kernel-server restart

Windows挂载linux目录：
	1. 控制面板 -> 程序和功能 -> 启用或关闭Windows功能 -> NFS服务 -> NFS客户端/管理工具 -> 确认
	2. Win+R -> cmd -> mount -h
	3. 此电脑 -> 右键 -> 映射网络驱动器：
	   驱动器：I:
	   文件夹：\\192.168.1.27\home\hx\share
	   勾选：登录时重新连接
	   勾选：使用其他凭据
```

