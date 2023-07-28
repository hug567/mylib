# Gitlab搭建：

## 1、ubuntu20搭建gitlab：

```bash
sudo apt install curl openssh-server ca-certificates postfix
# https://packages.gitlab.com/gitlab/gitlab-ce
curl -s https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.deb.sh | sudo bash
sudo apt install gitlab-ce

# 配置文件：
/etc/gitlab/gitlab.rb
#------------------------------------------------------#
external_url 'http://192.168.124.27:9002'
#------------------------------------------------------#
# 重新配置gitlab
sudo gitlab-ctl reconfigure
# 重启gitlab
sudo gitlab-ctl restart
# 访问
http://192.168.124.27:9002/

# 初始化root密码
/opt/gitlab/bin
#
sudo gitlab-ctl refconfigure
sudo gitlab-rails console -e production
```

