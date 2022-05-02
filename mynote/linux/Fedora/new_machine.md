## 1、新机器配置：

```c
// 创建新用户
sudo adduser hx                         //创建用户
sudo passwd hx                          //设置密码
sudo deluser -r hx                      //删除用户

// 设置软件源
cd /etc/yun.repos.d

sudo curl -o fedora.repo http://mirrors.aliyun.com/repo/fedora.repo
sudo curl -o fedora-updates.repo http://mirrors.aliyun.com/repo/fedora-updates.repo

sudo yum makecache

// 开启ssh server
sudo systemctl start sshd.service
sudo systemctl enable sshd.service

sudo iptables -I INPUT -p tcp --dport 22 -j ACCEPT
sudo vi /etc/ssh/ssh_config
    //取消注释
    PasswordAuthentication yes
    Port 22

// 安装常用软件
sudo yum -y install vim git zsh tmux
```

## 2、yum常见用法：

```c
yum makecache                           //缓存软件包信息
yum clean all                           //清除缓存
yum -y install xxx                      //安装软件
yum list | grep xxx                     //列举所有软件
yum list installed                      //列举已安装的软件
yum repolist                            //列举软件包仓库
```

