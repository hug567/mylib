## 1、Ubuntu 18.04安装docker：

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
docker rm <CONTAINER ID>                                    # 删除指定容器
docker rm $(docker ps -aq)                                  # 删除所有容器

# docker使用容器制作Image：
sudo docker commit <CONTAINER ID> huangxing/myopensuse:latest
```

## 2、openSUSE入门：

```shell
zypper lr --detail                                          # 列出软件源
zypper rr <id>                                              # 删除软件源

# 默认官方源
1 | NON OSS         http://download.opensuse.org/distribution/leap/42.3/repo/non-oss/suse/
2 | NON OSS Update  http://download.opensuse.org/update/leap/42.3/non-oss/
3 | OSS             http://download.opensuse.org/distribution/leap/42.3/repo/oss/suse/
4 | OSS Update      http://download.opensuse.org/update/leap/42.3/oss/

# 添加软件源
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/distribution/leap/42.3/repo/non-oss/ 'TX NON OSS'
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/distribution/leap/42.3/repo/oss/ 'TX OSS'
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/update/leap/42.3/non-oss/ 'TX NON OSS Update'
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/update/leap/42.3/oss/ 'TX OSS Update'
zypper refresh                                              # 更新软件源

zypper se <name>                                            # 搜索软件
zypper in <name>                                            # 安装软件
zypper rm <name>                                            # 删除软件
zypper up <name>                                            # 更新软件

# opensuse添加语言包
locale                                                      # 查看locale设置
locale -a                                                   # 查看当前locale设置
mv /home/hx/tools/locale-gen /usr/sbin                      # 从宿主机中拷贝一个locale-gen
mv /home/hx/tools/i18n/ /usr/share/                         # 从宿主机拷贝locale文件
vim /etc/locale.gen                                         # 修改locale配置文件
en_US.UTF-8 UTF-8
zh_CN.UTF-8 UTF-8
mkdir -p /usr/lib/locale                                    # 创建保存生成文件目录
locale-gen                                                  # 根据配置文件生成locale
```