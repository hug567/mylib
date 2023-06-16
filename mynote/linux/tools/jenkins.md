# 1、搭建jenkins：

```bash
# 推荐：sudo apt install openjdk-11-jdk
java --version

# 导入Jenkins存储库的GPG密钥

sudo apt update
sudo apt install openjdk-11-jdk
wget -q -O - https://pkg.jenkins.io/debian/jenkins.io.key | sudo apt-key add -
sudo sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'
sudo apt update
sudo apt install jenkins
sudo systemctl status jenkins

# Jenkins安装程序创建的初始的32个字符长的字母数字密码
sudo cat /var/lib/jenkins/secrets/initialAdminPassword

# 搜索docker镜像
docker search jenkinsci/blueocean
# 下载docker镜像
docker pull jenkinsci/blueocean
```

