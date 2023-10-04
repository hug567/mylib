# Gitlab搭建：

## 1、ubuntu20搭建gitlab：

```bash
sudo apt install curl openssh-server ca-certificates postfix
# https://packages.gitlab.com/gitlab/gitlab-ce
curl -s https://packages.gitlab.com/install/repositories/gitlab/gitlab-ce/script.deb.sh | sudo bash
sudo apt install gitlab-ce

# 配置文件：
sudo vim /etc/gitlab/gitlab.rb
#------------------------------------------------------#
external_url 'http://192.168.124.27:9002'
#------------------------------------------------------#
# 重新配置gitlab
sudo gitlab-ctl reconfigure
# 重启gitlab
sudo gitlab-ctl restart
```
## 2、配置gitlab：
### 1)、密码设置：
```bash
# 初始化root密码
#cd /opt/gitlab/bin

# 打开控制台
sudo gitlab-rails console -e production
# 查看所有用户
User.all
# 获取用户
u=User.where(id:1).first
# 设置密码(root)
u.password='Abc123,456'
# 确认密码
u.password_confirmation='Abc123,456'
# 保存密码
u.save!
# 登录gitlab
http://192.168.124.27:9002/
```

### 2)、修改数据目录：
```bash
sudo vim /etc/gitlab/gitlab.rb
#------------------------------------------------------#
git_data_dirs({
  "default" => {
    "path" => "/disk/sda/gitlab"
   }
})
#------------------------------------------------------#
# 旧数据迁移到新目录
cp -ar /var/opt/gitlab/git-data/repositories /disk/sda/gitlab
sudo gitlab-ctl reconfigure
sudo gitlab-ctl restart
```

### 3)、使能git lfs：

```bash
sudo vim /etc/gitlab/gitlab.rb
#------------------------------------------------------#
gitlab_rails['lfs_enabled'] = true
gitlab_rails['lfs_storage_path'] = "/disk/sda/gitlab/lfs"
#------------------------------------------------------#
sudo gitlab-ctl reconfigure
sudo gitlab-ctl restart
```

### 4)、使能https：

```bash
cd /etc/gitlab
mkdir ssl
cd ssl
# 复制已制作好的私钥和证书
sudo cp ~/tools/ssl/private.key ~/tools/ssl/certificate.crt .

sudo vim /etc/gitlab/gitlab.rb
#------------------------------------------------------#
external_url 'https://192.168.124.27:9003'
nginx['ssl_certificate'] = "/etc/gitlab/ssl/certificate.crt"
nginx['ssl_certificate_key'] = "/etc/gitlab/ssl/private.key"
# 重定向http到https
nginx['redirect_http_to_https'] = true
nginx['redirect_http_to_https_port'] = 9002
#------------------------------------------------------#
sudo gitlab-ctl reconfigure
sudo gitlab-ctl restart

# 访问
http://10.110.0.3:9002
https://10.110.0.3:9003
```

## 3、网页端配置：

```bash
# 设置中文
Perferences -> Localization -> Language -> Chinese, Simplified - 简体中文 (98% translated) -> Save changes
```

## 4、Gitlab升级：

```bash
# ubuntu 22.04 (gitlab-ce 16.4.1-ce.0)
# 跳过自动备份
sudo touch /etc/gitlab/skip-auto-backup
# 更新源信息
sudo apt update
# 查看可升级的版本，gitlab-ce或gitlab-ee
apt list --upgradable | grep gitlab
# 升级至gitlab最新版本
sudo apt install gitlab-ce

# 升级到指定版本
sudo apt update
apt-cache madison gitlab-ce | grep 16.3
sudo apt install gitlab-ce=16.3.0-ce.0

# 重启gitlab
sudo gitlab-ctl reconfigure
sudo gitlab-ctl restart
```

