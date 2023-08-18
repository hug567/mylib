# 1、下载：

```bash
docker pull ubuntu:18.04

docker run -it --net=host ubuntu:18.04 /bin/bash

# 基本工具：
sudo apt install lsb-release
# 时区：Asia/Shanghai
sudo apt install tzdata
```

# 2、环境设置：

## 1)、语言：

```bash
# 先设置好locale再安装其他文件
sudo apt install locales
# 安装语言：en_US.UTF-8，默认语言：en_US.UTF-8
sudo locale-gen "en_US.UTF-8"
sudo dpkg-reconfigure locales 
sudo update-locale LANG="en_US.UTF-8"

export LANG=en_US.UTF-8
export LANGUAGE=en_US.UTF-8
export LC_ALL=en_US.UTF-8

locale
locale -a

# 如果使用
```

## 2）、xx：

```bash
xx
```



