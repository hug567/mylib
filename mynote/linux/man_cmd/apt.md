# 1、常用命令

```bash
apt-cache search xxx                  # 搜索软件包
apt-cache depends xxx                 # 查看软件包依赖

apt download xxx                      # 下载deb包
apt list --installed                  # 显示已安装的包

sudo apt update                       # 更新镜像源
sudo apt intall xxx                   # 安装软件包及其依赖
sudo apt remove xxx                   # 删除软件包，不删除依赖，保留配置文件
sudo apt prune xxx                    # 删除软件包及依赖，删除配置文件
```
