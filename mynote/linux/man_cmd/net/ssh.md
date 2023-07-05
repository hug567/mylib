# 1、ssh：

```bash
sudo apt install openssh-client openssh-server

# 连接默认端口22
ssh user@192.168.0.101
# 指定端口连接
ssh -p1000 user@192.168.0.101
```

# 2、ssh-keygen：

```bash
# 生成密钥
ssh-keygen -t rsa -C "<hint information>"
ssh-keygen -t rsa -C "huangxing567@163.com"
# 指定目录
ssh-keygen -t rsa -f /var/jenkins_home -C "huangxing567@163.com"
```

# 3、ssh-copy-id：

```bash
# 拷贝公钥到远端机器
ssh-copt-id user@192.168.0.101
# 指定端口
ssh-copt-id -p1000 user@192.168.0.101
```

