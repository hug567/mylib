# 1、搭建jenkins：
## 1)、安装：
```bash
# 中文文档
https://www.jenkins.io/zh/doc/

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

# 下载docker镜像：https://www.jenkins.io/download/
docker pull jenkins/jenkins:lts-jdk11
# 运行jenkins镜像
docker run -u root --rm -d -p 8080:8080 -p 50000:50000 -v /home/hx/code/jenkins/home:/var/jenkins_home -v /home/hx/code/jenkins/root:/root -v /var/run/docker.sock:/var/run/docker.sock jenkins/jenkins:lts-jdk11
```
## 2)、配置：
```bash
# 访问jenkins
http://10.110.192.42:8080
# 管理员密码
docker exec -it 092906ae278a bash
cat /var/jenkins_home/secrets/initialAdminPassword

# 生成ssh密钥
ssh-keygen -t rsa -C "jenkins docker main"
# 发送公钥到远程主机
ssh-copy-id -p1000 user@192.168.0.101
# 验证连接
ssh -p1000 user@192.168.0.101

# 添加私钥到jenkins凭据
Dashboard -> 系统管理 -> 凭据 -> 域 -> 添加凭据
```

