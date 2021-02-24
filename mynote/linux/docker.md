### 1、Ubuntu 18.04安装docker：

```shell
dpkg -l | grep docker                                       # 查看是否安装了docker
sudo apt remove --purge docker.io                           # 卸载docker.io
sudo apt install docker.io                                  # 安装docker

sudo docker info                                            # 查看docker系统信息
sudo docker version                                         # 查看docker版本信息

sudo gpasswd -a $USER docker && newgrp docker               # 当前用户加入docker用户组

docker search hello-world                                   # 查询镜像
docker pull hello-world                                     # 拉取镜像

# 设置国内源
sudo vim /etc/docker/daemon.json
# 文件中写入
{
  "registry-mirrors": [
        "https://docker.mirrors.ustc.edu.cn/",
        "https://hub-mirror.c.163.com",
        "https://registry.docker-cn.com",
        "https://dockerhub.azk8s.cn",
        "https://reg-mirror.qiniu.com",
        "https://registry.docker-cn.com"
  ]
}
# 重启docker
sudo systemctl restart docker

sudo systemctl start docker                                 # 启动docker
sudo systemctl daemon-reload                                # 重启docker守护进程
sudo systemctl restart docker.service                       # 重启docker服务

docker search opensuse                                      # 搜索镜像
docker pull opensuse                                        # 拉取镜像
docker images                                               # 查看镜像
docker run -it opensuse:latest /bin/bash                    # 启动容器
exit                                                        # 推出容器
docker ps -a                                                # 查看容器
docker rm $(docker ps -aq)                                  # 删除所有容器
```