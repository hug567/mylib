# 搭建VPN服务器

## 1、Ubuntu配置VPN服务器

```bash
# 将安装：openven.service
sudo apt install openvpn libssl-dev openssl easy-rsa (lzop)

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
#--------------------------------------------------------#
export KEY_NAME="vpnairgens"
#--------------------------------------------------------#
sudo ./easyrsa init-pki
sudo ./easyrsa build-ca nopass
ls pki
#-rw------- 1 root root 1204 Jul 20 21:16 pki/ca.crt
#-rw------- 1 root root 1704 Jul 20 21:16 pki/private/ca.key
```

### 2)、制作Server端证书：

```bash
sudo ./easyrsa build-server-full vpnairgens nopass
#-rw------- 1 root root 4626 Jul 20 21:22 pki/issued/vpnairgens.crt
#-rw------- 1 root root 1704 Jul 20 21:22 pki/private/vpnairgens.key
```


### 3)、制作Client端证书：

```bash
sudo ./easyrsa build-client-full airgens nopass
#-rw------- 1 root root 4491 Jul 20 21:24 pki/issued/airgens.crt
#-rw------- 1 root root 1704 Jul 20 21:24 pki/private/airgens.key
```

### 4)、生成Diffie-Hellman文件：

```bash
sudo ./easyrsa gen-dh
#-rw------- 1 root root 424 Jul 20 21:30 pki/dh.pem
```

### 5)、复制证书文件：

```bash
sudo cp pki/ca.crt pki/issued/vpnairgens.crt pki/private/vpnairgens.key pki/dh.pem ..
cd ..
sudo cp dh.pem dh2048.pem
```

### 6)、配置vpn server：

```bash
sudo vim server.conf
#--------------------------------------------------------#
port 1194

proto tcp
;proto udp

ca ca.crt
cert vpnairgens.crt
key vpnairgens.key

server 10.110.1.0 255.255.255.0

comp-lzo
;tls-auth ta.key 0

status /var/log/openvpn/openvpn-status.log
;log /var/log/openvpn/openvpn.log
log-append /var/log/openvpn/openvpn.log

;mute 20
;explicit-exit-notify 1
#--------------------------------------------------------#
```

### 7)、运行vpn server：

```bash
cd ~
nohup /usr/sbin/openvpn --config /etc/openvpn/server.conf &
# 查看日志
tail -f /var/log/openvpn/openvpn.log
```

## 2、openvpn客户端：

- [OpenVPN客户端(Windows/Linux/MacOS)连接OpenVPN服务器](https://luanlengli.github.io/2019/11/25/OpenVPN%E5%AE%A2%E6%88%B7%E7%AB%AF-Windows-Linux-MacOS-%E8%BF%9E%E6%8E%A5OpenVPN%E6%9C%8D%E5%8A%A1%E5%99%A8.html)

- [openvpn.net](https://openvpn.net/client/client-connect-vpn-for-windows/)



# 方案二：

## 1、ubuntu安装openvpn server：

```bash
wget https://git.io/vpn -O openvpn-install.sh
wget https://raw.githubusercontent.com/Nyr/openvpn-install/master/openvpn-install.sh
chmod +x openvpn-install.sh
# protocol: UDP
sudo ./openvpn-install.sh
# service:
sudo systemctl start/stop/status/restart openvpn-server@server.service
# 凭证文件：
/root/client.ovpn
```

## 2、windows opvpnclient链接：

```bash
# 从服务器下载client配置文件：

```





















vpn服务器

客户端证书

用户认证

定义VPN路由

定义网络地址转换(NAT)规则