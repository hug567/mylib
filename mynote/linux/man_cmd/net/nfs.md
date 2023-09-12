# 1、安装软件：

## 1.1、nfs server：

```bash
# ubuntu 22.04
sudo apt install nfs-kernel-server             # 主机安装NFS Server
# 创建共享目录
cd ~
mkdir share
chmod 777 share
# nfs设置共享目录
sudo vim /etc/exports
#------------------------------------------------------#
/home/hx/share *(rw,nohide,insecure,no_subtree_check,async,no_root_squash)
#------------------------------------------------------#
sudo exportfs -arv                             # 更新export配置
sudo systemctl restart nfs-server.service      # 重启NFS服务

showmount -e
```

## 1.2、nfs client：

```bash
# 虚拟机：
mkdir share
# 挂载主机目录：qemu linux-5.10
mount -t nfs -o nolock,vers=4 192.168.0.100:/home/hx/share /share
# zynq7020/petalinux 2019.1
mount -t nfs -o nolock,vers=3 10.110.0.3:/home/hx/share /home/root/nfs/
```

