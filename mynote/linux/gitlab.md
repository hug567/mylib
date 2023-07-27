# Gitlab搭建：

## 1、ubuntu20搭建gitlab：

```bash
sudo apt install curl openssh-server ca-certificates postfix
# https://packages.gitlab.com/gitlab/gitlab-ce
curl -s https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.deb.sh | sudo bash
sudo apt install gitlab-ce

# 配置文件：
/etc/gitlab/gitlab.rb
```

