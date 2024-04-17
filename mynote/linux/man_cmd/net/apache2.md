# 1、搭建文件服务器：

```bash
# ubuntu 18.04/22.04
sudo apt install apache2
sudo mkdir /disk/sda/apache2

# 修改监听端口
sudo vim /etc/apache2/ports.conf
#----------------------------------------------#
Listen 9008
#----------------------------------------------#

# 修改根目录
sudo vim /etc/apache2/sites-available/000-default.conf
#----------------------------------------------#
<VirtualHost *:9008>
	DocumentRoot /disk/sda/apache2
#----------------------------------------------#

# apache2可访问新目录：
sudo vim /etc/apache2/apache2.conf
#----------------------------------------------#
# 修改：
<Directory /disk/sda/apache2>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
</Directory>
#----------------------------------------------#

# 重启apache2
sudo systemctl restart apache2
# 浏览器访问
http://10.110.0.3:9008
```

# 2、配置多站点：

- 同一台服务器上运行多个网站：

```bash
sudo vim /etc/apache2/ports.conf
#----------------------------------------------#
Listen 9008
# 新增：
Listen 9010
#----------------------------------------------#

# 新增站点：
cd /etc/apache2/sites-available
sudo cp 000-default.conf gitbook.conf
sudo vim gitbook.conf
#----------------------------------------------#
<VirtualHost *:9010>
	DocumentRoot /disk/sda/gitbook
#----------------------------------------------#

# 增加新站点目录访问权限：
sudo vim /etc/apache2/apache2.conf
#----------------------------------------------#
# 新增：
<Directory /disk/sda/gitbook>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
</Directory>
#----------------------------------------------#

cd /etc/apache2/sites-enabled
sudo ln -s ../sites-available/gitbook.conf gitbook.conf
# 重写配置：
sudo a2enmod rewrite
# 重启apache2
sudo systemctl restart apache2
# 浏览器访问
http://10.110.0.3:9010
```