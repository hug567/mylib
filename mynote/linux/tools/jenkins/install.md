# 1、搭建jenkins：
## 1)、安装：
- 本机安装：
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
```

- docker安装（推荐）：

```bash
# 下载docker镜像：https://www.jenkins.io/download/
docker pull jenkins/jenkins:lts-jdk11
# 创建jenkins数据存储目录：
cd /home/hx/code
mkdir -p jenkins/home jenkins/root
# 运行jenkins镜像：
# 将home和root目录映射到本机中，即使重新启动新的docker容器，配置好的原jenkins系统仍然存在：
docker run -u root --rm -d -p 8080:8080 -p 50000:50000 -v /home/hx/code/jenkins/home:/var/jenkins_home -v /home/hx/code/jenkins/root:/root -v /var/run/docker.sock:/var/run/docker.sock jenkins/jenkins:lts-jdk11

# 若容器启动失败，查看启动日志：
docker logs <ID>
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

# 2、使用：

## 1)、安装插件：

```bash
Dashboard -> Manage Jenkins -> Available plugins
# 安装插件：选中 -> 安装
SSH Agent
SSH Server
SSH Build Agents
# 确认安装：
Installed plugins -> ssh

# 启用SSH Server：
Dashboard -> Manage Jenkins -> Security -> SSH Server -> 随机选取 -> 保存
```

## 2）、添加凭据：

```bash
# 在jenkins中添加子节点的凭据：
Dashboard -> Manage Jenkins -> 凭据管理 -> 全局 -> Add Credentials
# New credentials：
#-------------------------------------------#
类型：Username with password
用户名：hx
密码：********
描述：10.110.0.3
#-------------------------------------------#
-> Create
```

## 3）、添加节点：

- jenkins host机器中配置：

```bash
# 进入jenkins docker，第一次进入是需使用exec
docker exec -it <container ID> bash
# 生成ssh秘钥，并发送到子节点：
ssh-keygen -t rsa -C "jenkins docker main"
ssh-copy-id hx@10.110.0.3
# 登录一次子节点，并复制.ssh到/var/jenkins_home
ssh hx@10.110.0.3
cp -r ~/.ssh/ /var/jenkins_home/
# 或添加新的机器时：
cp ~/.ssh/known_hosts /var/jenkins_home/.ssh/
```

- 子节点机器配置：

```bash
# 在子节点机器中安装java：
sudo apt install openjdk-11-jdk
java --version
# 在子节点机器中创建工作目录，注意远程用户访问权限：
mkdir -p ~/code/jenkins/workspace
```

- ubuntu18新机器作为jenkins子节点需配置：

```bash
/etc/apt/sources.list
/etc/netplan/01-network-manager-all.yaml
sudo apt install openjdk-11-jdk docker.io openssh-server
```

- jenkins网页中添加子节点：

```bash
Dashboard -> Manage Jenkins -> Nodes -> New Node -> 节点名称：main -> 选中“固定节点” -> Create
#-------------------------------------------#
# 节点配置：
名字：main
Number of executors： 1
远程工作目录：~/code/jenkins/workspace         # 重要：上面添加的凭据所属的用户，需可访问整个远程工作目录
启动方式：Lauch agents via SSH
主机：10.110.0.3
Credentials: hx                             # 上一步添加的凭据
#-------------------------------------------#
-> 保存 -> 刷新状态
```

## 4）、添加新任务：

```bash
Dashboard -> 新建Item -> “test01” -> 流水线 -> 确定 -> 保存
# 测试任务：
配置 -> 流水线 -> Pipeline script
#------------------------------------#
pipeline {
    agent {
        label "main"
    }

    stages {
        stage('Hello') {
            steps {
                sh 'whoami; uname -a; pwd; ifconfig -a; cat /etc/os-release'
            }
        }
    }
}
#------------------------------------#
保存 -> 立即构建
```

## 5）、创建带参数的工程：

```bash
# 安装插件：
Dashboard -> 系统管理 -> 插件管理 -> Available plugins：
#------------------------------------#
Build With Parameters
Persistent Parameter
#------------------------------------#

# 新建参数化工程：
# 布尔参数值：true/false
Dashboard -> 新建任务 -> “test02” -> 流水线 -> 确定 -> 勾选“参数化构建工程” -> 添加参数 -> 布尔值参数
#------------------------------------#
名称：download_code
勾选：“Set by Default”
描述：是否重新下载代码
#------------------------------------#
-> 脚本
#------------------------------------#
pipeline {
    agent {
        label "node05"
    }

    stages {
        stage('stage01') {
            steps {
                sh 'echo "download_code: ${download_code}"'
            }
        }
    }
}
#------------------------------------#
-> 保存
```

