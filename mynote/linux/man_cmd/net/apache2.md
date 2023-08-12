# 1、搭建文件服务器：

```bash
# ubuntu 22.04
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
sudo vim /etc/apache2/apache2.conf
#----------------------------------------------#
<Directory /disk/sda/apache2>
#----------------------------------------------#

# 重启apache2
sudo systemctl restart apache2
# 浏览器访问
http://10.110.0.3:9008
```

