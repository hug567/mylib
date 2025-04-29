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
docker pull wordpress
docker run -it --name wordpress -p 9999:80 -v /usr/local/share/wordpress:/var/www/html -d wordpress

 docker run -d --name mysql -v /usr/local/share/mysql/data:/var/lib/mysql -v /usr/local/share/mysql/conf:/etc/mysql/conf.d -v /usr/local/share/mysql/logs:/var/log/mysql -p 3306:3306 -e MYSQL_ROOT_PASSWORD=123456 mysql:8
```

