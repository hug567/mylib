# 1、ssh：

## 1）、常见用法：

```bash
sudo apt install openssh-client openssh-server

# 连接默认端口22
ssh user@192.168.0.101
# 指定端口连接
ssh -p1000 user@192.168.0.101

# 清除已知用户：
# linux:
ssh-keygen -f $HOME/.ssh/known_hosts -R 192.168.0.2
# windows:
cd C:\Users\rhosoon\.ssh
ssh-keygen -f known_hosts -R 192.168.0.2
```

## 2）、跳板机登录：

```bash
# ssh通过跳板机登录内部机器
ssh hx@172.22.195.55 -J rhosoon@192.168.99.143    # ssh 内部机器 -J 跳板机
# 通过跳板机登录时指定端口
ssh hx@172.22.195.55 -p 22 -J rhosoon@192.168.99.143:22
# 经过多个跳板机
ssh hx@172.22.195.55 -p 22 -J user1@192.168.0.1:22,user2@192.168.1.1:22

# 写在配置文件中：
vim ~/.ssh/config
#------------------------------------------------#
Host 172.22.195.55
    HostName 172.22.195.55
    Port 22
    User hx
    ProxyJump rhosoon@192.168.99.143:22
#------------------------------------------------#
# 连接：
ssh hx@172.22.195.55
ssh 172.22.195.55
# scp拷贝文件：
scp file.txt hx@172.22.195.55:~
scp hx@172.22.195.55:~/file.txt ./

# 通过跳板机访问内部机器，先在~/.ssh/config中配置：
#------------------------------------------------#
Host antenna
    User root
    Hostname 192.168.0.2
    ProxyCommand ssh rhosoon@192.168.99.50 -W %h:%p B
#------------------------------------------------#
# 拷贝文件到内部机器：
scp file antenna:~
# 从内部机器拷贝文件到本地：
scp antenna:/etc/repoinfo ./
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
# 拷贝公钥到远端机器: ~/.ssh/authorized_keys
ssh-copy-id user@192.168.0.101
# 指定端口
ssh-copt-id -p1000 user@192.168.0.101
```

#  4、配置config：

```bash
# 配置文件：~/.ssh/config
Host hx
        HostName 10.110.0.3
        User hx
        Port 22
```

