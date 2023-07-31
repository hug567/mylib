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
### 1)、密码设置
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

### 2)、修改数据目录
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

## 3、网页端配置：

```bash
# 设置中文
Perferences -> Localization -> Language -> Chinese, Simplified - 简体中文 (98% translated) -> Save changes
```

