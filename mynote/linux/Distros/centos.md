# 1、Centos安装软件：

```shell
yum makecache                            # 缓存软件包信息
yum clean all                            # 清除缓存
yum-config-manager --enable "repo id"    # 启用仓库
yum-config-manager --disable "repo id "  # 禁用仓库
yum repolist                             # 列举软件包仓库
yum list                                 # 列举所有软件
yum reinstall <package>                  # 重新安装软件包
yum remove <package>                     # 卸载软件包
yum update <package>                     # 更新软件包
yum search <package>                     # 查找是否已安装某个软件包
yum downgrage <package>                  # 降级软件包
yum check-update                         # 检查可用的更新
yum deplist <package>                    # 查询软件包的依赖

# 备份软件源：
mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo.backup

# 查看Centos版本：
cat /etc/redhat-release

# 设置阿里软件源：
# Centos 7:
wget -O /etc/yum.repos.d/CentOS-Base.repo https://mirrors.aliyun.com/repo/Centos-7.repo
curl -o /etc/yum.repos.d/CentOS-Base.repo https://mirrors.aliyun.com/repo/Centos-7.repo
# Centos 8:
wget -O /etc/yum.repos.d/CentOS-Base.repo https://mirrors.aliyun.com/repo/Centos-8.repo
curl -o /etc/yum.repos.d/CentOS-Base.repo https://mirrors.aliyun.com/repo/Centos-8.repo

# 安装常用软件, 使用与Ubuntu相同的配置文件即可
yum -y install vim                       # 安装vim
yum -y install tmux                      # 安装tmux
yum -y install zsh                       # 安装zsh

# 问题1：
Failed to set locale, defaulting to C.UTF-8
```