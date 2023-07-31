# 搭建tftp服务器：

## 1、ubuntu：

- 已验证：ubuntu 22.04、ubuntu16.04

```bash
# 安装tftp
sudo apt install tftp-hpa tftpd-hpa xinetd
# 创建tftp根目录
cd ~/temp; mkdir tftpboot; chmod 777 tftpboot
# 编辑配置文件
sudo vim /etc/default/tftpd-hpa
/* ------------------------------------------------------------ */
# /etc/default/tftpd-hpa

TFTP_USERNAME="tftp"
TFTP_DIRECTORY="/home/hx/temp/tftpboot"
TFTP_ADDRESS="0.0.0.0:69"
#TFTP_OPTIONS="--secure"
TFTP_OPTIONS="-l -c -s"
/* ------------------------------------------------------------ */
# 重启tftp
sudo service tftpd-hpa restart

# 测试连接：
cd ~
tftp localhost                                          # 连接至本机
tftp> get test1.txt                                     # 获取文件
tftp> put test2.txt                                     # 上传文件
tftp> q                                                 # 退出连接
```

