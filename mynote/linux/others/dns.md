# DNS服务器搭建

## 1、搭建dns服务器：

```bash
# dns端口号：53
sudo apt install bind9 bind9utils bind9-doc
cd /etv/bind
sudo vim named.conf.local
#--------------------------------------------------#
zone "gitlab.huangxing.com" {
    type master;
    file "db.gitlab.huangxing.com";
};
#--------------------------------------------------#

sudo cp /etc/bind/db.local /var/cache/bind/db.gitlab.huangxing.com
sudo vim /var/cache/bind/db.gitlab.huangxing.com
#--------------------------------------------------#
# 在末尾添加，将解析gitlab.huangxing.com -> 192.168.124.27
@       IN      A       192.168.124.27
#--------------------------------------------------#
sudo systemctl restart bind9.service

# bind9.service控制
sudo systemctl start bind9.service
sudo systemctl stop bind9.service
sudo systemctl restart bind9.service
sudo systemctl reload bind9.service
sudo systemctl status bind9.service
```

- 测试dns服务器：

```bash
sudo vim /etc/resolv.conf
#--------------------------------------------------#
nameserver 192.168.124.27
#--------------------------------------------------#
ping gitlab.huangxing.com
```

- windows添加dns服务器：
```bash
控制面板 -> 网络和共享中心 -> 更改适配器设置 -> 在对应网卡上右键 -> 属性
-> Internet 协议版本 4 (TCP/IPv4) -> 属性 -> 高级 -> DNS -> 添加
# 添加默认的dns服务器和自定义的dns服务器，可添加多个
# 如：192.168.124.1, 192.168.124.27
-> 确定 -> 确定 -> 关闭

# 浏览器验证
https://gitlab.huangxing.com
```