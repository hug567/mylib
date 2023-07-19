# 搭建VPN服务器

## 1、Ubuntu配置VPN服务器

```bash
# openven.service
sudo apt install openvpn libssl-dev openssl easy-rsa

openvpn --version

# openvpn证书：CA证书、Server端证书、Client端证书
```

### 1）、制作CA证书：

```bash
cd /etc/openvpn
sudo mkdir easy-rsa
cd easy-rsa
sudo cp -r /usr/share/easy-rsa/* .
sudo cp vars.example vars
sudo vim vars
```







vpn服务器

客户端证书

用户认证

定义VPN路由

定义网络地址转换(NAT)规则