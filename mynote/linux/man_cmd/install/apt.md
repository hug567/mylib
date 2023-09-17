# 1、常用命令

```bash
apt-cache search xxx                  # 搜索软件包
apt-cache depends xxx                 # 查看软件包依赖
apt-cache madison vim                 # 查看软件有哪些版本

apt download xxx                      # 下载deb包
apt list --installed                  # 显示已安装的包

sudo apt update                       # 更新镜像源
sudo apt intall xxx                   # 安装软件包及其依赖，或升级到最新版本
sudo apt remove xxx                   # 删除软件包，不删除依赖，保留配置文件
sudo apt --prune remove xxx           # 删除软件包及其配置文件
sudo apt prune xxx                    # 删除软件包及依赖，删除配置文件
sudo apt --only-upgrade install xxx   # 仅更新指定软件包，若未安装，则直接退出

# 查看包信息(版本、依赖等)
apt show xxx
```
