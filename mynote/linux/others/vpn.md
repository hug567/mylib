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

### 1）、安装：

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

### 2）、重启openvpn：

```bash
sudo systemctl restart openvpn-server@server.service
```

### 3）、设置用户名密码登录：

- 添加脚本：

```bash
sudo vim /etc/openvpn/checkpsw.sh 
```

```bash
#!/bin/sh
###########################################################
# checkpsw.sh (C) 2004 Mathias Sundman 
#
# This script will authenticate OpenVPN users against
# a plain text file. The passfile should simply contain
# one row per user with the username first followed by
# one or more space(s) or tab(s) and then the password.

PASSFILE="/etc/openvpn/psw-file"
LOG_FILE="/etc/openvpn/openvpn-password.log"
TIME_STAMP=`date "+%Y-%m-%d %T"`

###########################################################

if [ ! -r "${PASSFILE}" ]; then
  echo "${TIME_STAMP}: Could not open password file "${PASSFILE}" for reading." >> ${LOG_FILE}
  exit 1
fi

CORRECT_PASSWORD=`awk '!/^;/&&!/^#/&&$1=="'${username}'"{print $2;exit}' ${PASSFILE}`

if [ "${CORRECT_PASSWORD}" = "" ]; then 
  echo "${TIME_STAMP}: User does not exist: username="${username}", password="${password}"." >> ${LOG_FILE}
  exit 1
fi

if [ "${password}" = "${CORRECT_PASSWORD}" ]; then 
  echo "${TIME_STAMP}: Successful authentication: username="${username}"." >> ${LOG_FILE}
  exit 0
fi

echo "${TIME_STAMP}: Incorrect password: username="${username}", password="${password}"." >> ${LOG_FILE}
exit 1
```

```bash
sudo chmod +x /etc/openvpn/checkpsw.sh
```
- 添加账号文件：
```bash
sudo vim /etc/openvpn/psw-file
#----------------------------------------------------------------#
user1 password1
user2 password2
user3 password3
#----------------------------------------------------------------#
```
- 更新server配置：
```bash
# 配置文件：/etc/openvpn/server.conf
#         /etc/openvpn/server/server.conf
sudo vim /etc/openvpn/server/server.conf
#- 在末尾添加：----------------------------------------------------#
script-security 3
auth-user-pass-verify /etc/openvpn/checkpsw.sh via-env
username-as-common-name
verify-client-cert none
client-to-client
#----------------------------------------------------------------#

# 重启openvpn server:
sudo systemctl restart openvpn-server@server.service
```
### 4）、设置静态ip：
```bash
# 设置指定用户获取静态ip：
sudo vim /etc/openvpn/server/ipp.txt
#- 尾部添加:  ----------------------------------------------------#
huangxing01,10.8.0.11,
#----------------------------------------------------------------#

# 重启openvpn server:
sudo systemctl restart openvpn-server@server.service
```


## 2、windows openvpn client连接：

```bash
# 从服务器下载client配置文件：
/root/client.ovpn
# 复制到openvpn client配置文件目录
C:\Users\Administrator\OpenVPN\config
# 启动openvpn连接，验证：
ping 10.8.0.1
```

## 3、linux openvpn client连接：

```bash
sudo apt install openvpn
#sudo cp client.ovpn /etc/openvpn/client
sudo openvpn --config client.ovpn
```

## 4、客户端设置使用账号密码连接：
```bash
cp client.ovpn huangxing01.ovpn
vim huangxing01.ovpn
#----------------------------------------------------------------#
client
dev tun
proto udp
remote 39.107.248.84 1194
resolv-retry infinite
nobind
persist-key
persist-tun
remote-cert-tls server
auth SHA512
cipher AES-256-CBC
ignore-unknown-option block-outside-dns
verb 3
# 增加使用用户名密码登录openvpn服务器配置：
auth-user-pass
# 删除cert和key
#----------------------------------------------------------------#

# 修改后使用账号密码连接
sudo openvpn --config huangxing01.ovpn
```
