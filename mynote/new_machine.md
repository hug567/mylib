### 1、配置源镜像：

```c
cd /etc/apt                                              //进入目录
sudo mv sources.list sources.list-ubuntu                 //备份源镜像
sudo gedit sources.list                                  //新建源镜像
deb http://mirrors.cloud.tencent.com/ubuntu/ bionic main universe restricted multiverse
deb http://mirrors.cloud.tencent.com/ubuntu/ bionic-security main universe restricted multiverse
deb http://mirrors.cloud.tencent.com/ubuntu/ bionic-updates main universe restricted multiverse
deb http://mirrors.cloud.tencent.com/ubuntu/ bionic-backports main universe restricted multiverse
deb-src http://mirrors.cloud.tencent.com/ubuntu/ bionic main universe restricted multiverse
deb-src http://mirrors.cloud.tencent.com/ubuntu/ bionic-security main universe restricted multiverse
deb-src http://mirrors.cloud.tencent.com/ubuntu/ bionic-updates main universe restricted multiverse
deb-src http://mirrors.cloud.tencent.com/ubuntu/ bionic-backports main universe restricted multiverse
sudo apt update                                          //更新源镜像
sudo apt upgrade                                         //更新软件
```
###  2、安装软件：

```C
sudo apt install vim vim-gnome git tmux zsh gcc g++ \
     make cmake python python3 ctags                     //安装软件
vim --version                                            //查看vim版本
git --version                                            //查看git版本
tmux -V                                                  //查看tmux版本
zsh --version                                            //查看zsh版本
gcc --version                                            //查看gcc版本
g++ --version                                            //查看g++版本
make --version                                           //查看make版本
cmake --version                                          //查看cmake版本
python --version                                         //查看python版本
python3 --version                                        //查看python3版本
```
### 3、配置GitHub：

```C
git config --global user.name "Huang Xing"               //设置用户名
git config --global user.email huangxing567@163.com      //设置邮箱
ssh-keygen -t rsa -C "huangxing567@163.com"              //配置SSH Key
cat ~/.ssh/id_rsa.pub                                    //查看SSH Key
```
### 4、下载配置文件：

```C
git clone git@github.com:hug567/myconfigure.git          //下载配置仓库
cp -a <...> ~                                            //复制配置文件
```

### 5、windows下Git Bash配置：

```c
//配置GitHub并下载mgconfigure仓库
将gitbash/tmux/bin下所有文件复制到.../Program Files/Git/usr/bin下
将gitbash/tmux/share下所有文件复制到.../Program Files/Git/use/share下

```

### 6、Ubuntu 18.04配置：

#### 1)、安装搜狗输入法
```c
sudo apt install fcitx                                   //安装fcitx
https://pinyin.sogou.com/linux/?r=pinyin                 //下载
sudo dpkg -i sogoupinyin_2.3.1.0112_amd64.deb            //安装(或双击)
Settings -> Region & Lanauage -> Manage Installed Languages  //设置
->  Keyboard input method ststem: fcitx                      //设置
-> Apply System-Wide -> 重启                                 //设置
-> 桌面右上角键盘图标 -> Configure Current Input Method      //设置
-> 左下角"+"图标 -> Search Input Method -> sogou -> OK       //设置
-> 将Sogou Pinyin移至第一位                                  //设置

//问题：输入法候选栏中文乱码
cd ~/.config                                             //进入配置目录
rm -rf Sogou* sogou*                                     //删除搜狗配置文件
```

#### 2)、取消锁屏
```c
Settings -> Power -> Blank screen -> Never               //取消锁屏
```


