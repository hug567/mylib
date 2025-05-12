# 1、环境准备：

- ubuntu 22.04：

```bash
sudo apt install apache2 php mysql-server php-mysql phpmyadmin
sudo ln -s /usr/share/phpmyadmin /var/www/html/phpmyadmin
sudo systemctl restart mysql.service
sudo systemctl restart apache2.service
```

# 2、docker部署wordpress：

```bash
# 拉取并运行wordpress镜像：
docker pull hub.c.163.com/library/wordpress:latest
docker tag hub.c.163.com/library/wordpress:latest wordpress:latest
docker rmi hub.c.163.com/library/wordpress:latest
docker run -it --name wordpress -p 9999:80 -v /usr/local/share/wordpress:/var/www/html -d wordpress

docker exec -it wordpress bash

# 网页打开以下地址，安装wordpress：
http://10.110.0.4:9999/wp-admin/setup-config.php

docker pull hub.c.163.com/library/mysql:8
docker tag hub.c.163.com/library/mysql:8 mysql:8
docker rmi hub.c.163.com/library/mysql:8

docker run -d --name mysql -v /usr/local/share/mysql/data:/var/lib/mysql -v /usr/local/share/mysql/conf:/etc/mysql/conf.d -v /usr/local/share/mysql/logs:/var/log/mysql -p 3306:3306 -e MYSQL_ROOT_PASSWORD=123456 mysql:8
# 进入mysql容器：
docker exec -it mysql /bin/bash
# 输入启动容器时设置的密码：
mysql -u root -p
# 设置mysql运行外部访问：
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
FLUSH PRIVILEGES;
# 创建数据库：
create database wordpress;
# 推出数据库命令行
exit

```

