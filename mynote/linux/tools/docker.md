# 1、Ubuntu 18.04安装docker：

```shell
dpkg -l | grep docker                                       # 查看是否安装了docker
sudo apt remove --purge docker.io                           # 卸载docker.io
sudo apt install docker.io                                  # 安装docker

sudo docker info                                            # 查看docker系统信息
sudo docker version                                         # 查看docker版本信息

sudo gpasswd -a $USER docker && newgrp docker               # 当前用户加入docker用户组(临时)，需重连服务器

docker search hello-world                                   # 查询镜像
docker pull hello-world                                     # 拉取镜像

# 设置国内源
sudo vim /etc/docker/daemon.json
# 文件中写入
{
  "registry-mirrors": [
        "https://docker.mirrors.ustc.edu.cn/",
        "https://hub-mirror.c.163.com/",
        "https://cr.console.aliyun.com/"
  ]
}
# 重启docker
sudo systemctl restart docker
# 查看镜像源
docker info

sudo systemctl start docker                                 # 启动docker
sudo systemctl daemon-reload                                # 重启docker守护进程
sudo systemctl restart docker.service                       # 重启docker服务

```

# 2、docker常用命令：

## 1)、常用命令：

```bash
docker
	-i                                                      # 交互式操作
	-t                                                      # 终端
	-d                                                      # 后台运行容器
	-v <host_dir>:<container_dir>                           # 映射host目录到容器
	--net=shot                                              # 使用host网络
```

## 2）、启动退出：

```bash
docker run -it opensuse:latest /bin/bash                    # 启动容器
exit                                                        # 退出并停止容器
Ctrl-P + Ctrl-Q                                             # 退出容器(不停止)
```

## 3）、镜像操作：

```bash
docker search opensuse                                      # 搜索镜像
docker pull opensuse                                        # 拉取镜像
docker pull ubuntu:18.04
docker pull ubuntu:20.04
docker pull ubuntu:22.04
docker pull fedora:35
docker pull opensuse/leap:15.3

# 镜像操作
docker images -h                                            # 查看image命令帮助
docker images                                               # 查看本地docker镜像
docker images -a                                            # 查看所有镜像
docker images -q                                            # 只显示IMAGE ID
docker images ubuntu                                        # 查看指定名称的容器
docker images ubuntu:18.04                                  # 查看指定名称和版本的容器
docker images ubuntu 18.04 -q                               # 只显示指定名称和版本的容器的ID
docker rmi ubuntu:latest                                    # 删除镜像
docker rmi <IMAGE ID>                                       # 删除镜像

# 打包容器为Image
sudo docker commit <CONTAINER ID> <huangxing/myopensuse:latest>
# 打包Image为文件
docker save -o <myopensuse.tar> <huangxing/myopensuse:latest>
# 从文件加载Image
docker load -i <myopensuse.tar>
```

## 4）、容器操作：

```bash
# 只查看启动的容器
docker ps
# 查看所有容器详细信息
docker ps -a
# 只查看启动的容器的ID
docker ps -q
# 只查看所有容器的id
docke ps -a -q
docker start <CONTAINER ID>                                 # 启动容器
docker stop <CONTAINER ID>                                  # 停止容器
docker attach <CONTAINER ID>                                # 进入容器
docker rm <CONTAINER ID>                                    # 删除指定容器
docker rm $(docker ps -aq)                                  # 删除所有容器

# 进入已启动的容器
docker exec -it <CONTAINER ID> bash
# docker启动centos
docker run -it centos:latest /bin/bash
# 映射host目录到容器
docker run -it -v /home/hx/data:/data centos:latest /bin/bash
# 启动容器可联网
docker run -it -v /home/hx/data:/data --net=host ubuntu:20.04 /bin/bash
# 以指定用户启动容器，同时指定工作目录
docker run --user hx -w /home/hx -it myubuntu:v1.0 /bin/bash
```

## 5)、文件操作：

```shell
# 从容器中拷贝文件到host:
docker cp <CONTAINER ID>:/root/.bashrc ./
docker cp <CONTAINER NAME>:/root/.bashrc ./

# 在host中拷贝文件进容器:
docker cp ~/.tmux.conf <CONTAINER ID>:/root
docker cp ~/.tmux.conf <CONTAINER NAME>:/root
```

# 3、dockfile：

```shell
# 进入dockerfile文件所在目录
cd .../dockerfile/

# 根据当前目录下的Dockfile文件构建image
docker build -t <jenkins:v1.0> ./
# 指定dockfile文件构建image
docker build -t <jenkins:v1.0> -f <jenkins.df> ./
```
