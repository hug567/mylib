## 1、配置源镜像：

```shell
sudo vi /etc/apt/sources.list
```

## 2、安装常用软件：

```shell
sudo apt install vim-gnome openssh-client openssh-server
sudo apt install git tmux zsh gcc g++ cmake python python3 u-boot-tools tig net-tools
sudo apt install htop
```

#### 1)、模糊搜索fzf：

```shell
cd ~
git clone https://hub.fastgit.org/junegunn/fzf.git
mv fzf .fzf
cd .fzf/bin
wget https://github.com/junegunn/fzf/releases/download/0.28.0/fzf-0.28.0-linux_amd64.tar.gz
tar
cd ..
./install

# 搜索历史命令：
Ctrl + R

# 搜索当前目录下文件：
fzf
```

