# 1、nginx搭建wget服务器：

```bash
# 安装nginx
sudo apt install nginx
# 查看版本
nginx -v
# 验证安装
sudo nginx -t
# 浏览器打开服务器ip
http://10.110.0.3

# 修改网站根目录
sudo vim /etc/nginx/sites-enabled/default
#-----------------------------------------------------------#
        listen 9004 default_server;
        listen [::]:9004 default_server;

        root /home/hx/nginx;
#-----------------------------------------------------------#

# 启动Ngnix
sudo service nginx start
# 停止Ngnix
sudo service nginx stop
# 重启Ngnix
sudo service nginx restart

# wget获取文件
wget http://10.110.0.3:9004/test.txt
# curl获取文件
wget http://10.110.0.3:9004/test.txt -o test.txt
```

