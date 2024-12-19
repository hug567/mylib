# 1、常用命令

```bash
apt-cache search xxx                  # 搜索软件包
apt-cache depends xxx                 # 查看软件包依赖
apt-cache rdepends xxx                # 查看软件包xxx被哪些包依赖
apt-cache madison vim                 # 查看软件有哪些版本

apt download xxx                      # 下载deb包
# 下载软件包及其所有依赖
apt download $(apt-cache depends --recurse --no-recommends --no-suggests --no-conflicts --no-breaks --no-replaces --no-enhances --no-pre-depends gcc-mipsel-linux-gnu | grep -v i386 | grep "^\w")
apt list --installed                  # 显示已安装的包

sudo apt update                       # 更新镜像源
sudo apt intall xxx                   # 安装软件包及其依赖，或升级到最新版本
sudo apt remove xxx                   # 删除软件包，不删除依赖，保留配置文件
sudo apt --prune remove xxx           # 删除软件包及其配置文件
sudo apt prune xxx                    # 删除软件包及依赖，删除配置文件
sudo apt --only-upgrade install xxx   # 仅更新指定软件包，若未安装，则直接退出

# 查看包信息(版本、依赖等)
apt show xxx
# 安装指定版本
apt-cache madison xxx
sudo apt install xxx=x.y.z
```

# 2、离线安装openssh-server：

- ubuntu 18.04：(未验证成功)

```bash
# 先在连网的ubuntu 18中下载openssh-server及其所有依赖的deb包：
apt download $(apt-cache depends --recurse --no-recommends --no-suggests --no-conflicts --no-breaks --no-replaces --no-enhances --no-pre-depends openssh-client | grep -v i386 | grep "^\w")
apt download $(apt-cache depends --recurse --no-recommends --no-suggests --no-conflicts --no-breaks --no-replaces --no-enhances --no-pre-depends openssh-server | grep -v i386 | grep "^\w")

# 在需要安装的机器上通过scp从下载deb包的机器上获取所有deb包：
scp -r hx@192.168.99.112:/tmp/openssh ./

# 安装所有deb包：
cd openssh
echo "$(ls *.deb)" | while read deb; do sudo dpkg -i $deb; done
```



