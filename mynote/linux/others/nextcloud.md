# Nextcloud私有云搭建

## 1、搭建nextcloud：

- 已验证：ubuntu 22.04

```bash
# 安装snap
sudo apt install snapd snapcraft php
# 安装nextcloud
sudo snap install nextcloud

# 查看安装
snap changes nextcloud
# 查看信息
snap info nextcloud
# 查看连接
snap connections nextcloud
# 启动nextcloud
sudo snap start nextcloud
# 停止nextcloud
sudo snap stop nextcloud
# 重启nextcloud
sudo snap restart nextcloud

# 修改访问端口(默认:80)
sudo snap set nextcloud ports.http=9000
sudo snap set nextcloud ports.https=9001
# 登录nextcloud
http://192.168.124.27:9000
```

## 2、网页端设置：

```bash
# 创建管理员账号
admin/admin
```

## 3、服务端配置：

```bash
# 配置文件(修改后不需要重启)：
/var/snap/nextcloud/current/nextcloud/config/config.php
# 数据目录
'datadirectory' => '/data',
# 信任域名
'trusted_domains' =>
array (
  0 => '192.168.124.27:443',
),


# 查看用户
sudo nextcloud.occ user:list
# 重置用户密码
sudo nextcloud.occ user:resetpassword admin
```

```bash
sudo nextcloud.occ config:system:get teusted_domains
sudo nextcloud.occ config:system:set teusted_domains 1 --value=example.com
```

### 2）、更改数据目录：

```bash
# 必须是/media或/mnt下的目录
cd /mnt
sudo cp -r /var/snap/nextcloud/common/nextcloud/ .
sduo vim /var/snap/nextcloud/current/nextcloud/config/config.php
#-----------------------------------------------------#
'datadirectory' => '/mnt/nextcloud/data',
#-----------------------------------------------------#

# wrap方案：
#   nextcloud/data/.ocdata仍放在/media或/mnt目录，data目录中其他目录软连接到其他磁盘目录中
```

## 4、配置自签名ssl证书：

```bash
# 生成自签名证书
sudo nextcloud.enable-https self-signed
# 重新登录nextcloud
https://192.168.124.27

# 若防火墙关闭了web端口，需重新打开
sudo ufw allow 80/tcp

# 关闭https访问
sudo nextcloud.disable-https
```

## 5、常见问题：

### 1)、登录：

- 我们检测到您的IP进行了多次无效登录尝试。因此，你的下一次登录最长会延迟30秒。

```bash
# 关闭暴力破解保护：
'auth.bruteforce.protection.enabled' => false,
```

### 2)、登录不上：

* 账号密码均正确，但登录灭反应，可能是浏览器缓存和cookie影响，清楚浏览器缓存和cookie，或者换一个浏览器试试；



## 99、docker启动nextcloud：

```bash

```

