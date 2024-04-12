# 1、网络代理：

## 1）、环境介绍：

- 共有2台机器，A机器有两个网卡，可同时访问外网(192.168.100.252)和内网(192.168.99.106)；B机器只能访问内网(192.168.99.141)；

## 2）、A机器配置：

```bash
# 安装squid：
sudo apt instll squid
# 修改配置文件：
cd /etc/squid
sudo cp squid.conf squid.conf-bkp
sudo vim  squid.conf
#-------------------------------------------#
# 可自定义监听端口：
http_port 3128
# 修改：
http_access deny all
# 为：
http_access allow all
#-------------------------------------------#
# 重启squid：
sudo systemctl restart squid
```

## 3）、B机器配置：

```bash
# 设置代理，192.168.99.106为A机器内网ip，B机器可ping通这个ip：
export http_proxy=http://192.168.99.106:3128
export https_proxy=https://192.168.99.106:3128
export no_proxy="127.0.0.1, localhost, 172.19.58.202，172.19.58.201"

# 测试：
wget baidu.com
# 注：经测试，wget可成功，但apt install失败
```

