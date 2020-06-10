# Ubuntu服务器部署Hexo博客

### 服务器配置

```C
sudo apt install nginx nodejs npm                        //安装软件
nginx -v                                                 //查看nginx版本
node -v                                                  //查看node版本
npm -v                                                   //查看npm版本
sudo nmp install n -g                                    //安装更新版本工具N
sudo n stable                                            //更新nodejs版本
npm ls --depth 0                                         //查看hexo安装的插件
sudo npm install -g hexo                                 //安装hexo
sudo nom install -g hexo-cli                             //安装hexo插件
sudo npm install hexo --save                             //安装hexo插件
sudo npm install hexo-deployer-git --save                //安装hexo插件
sudo npm install hexo-generator-archive --save           //安装hexo插件
sudo npm install hexo-generator-category --save          //安装hexo插件
sudo npm install hexo-generator-index --save             //安装hexo插件
sudo npm install hexo-generator-tag --save               //安装hexo插件
sudo npm install hexo-renderer-ejs --save                //安装hexo插件
sudo npm install hexo-renderer-marked --save             //安装hexo插件
sudo npm install hexo-renderer-stylus --save             //安装hexo插件
sudo npm install hexo-server                             //安装hexo插件
hexo -v                                                  //查看hexo版本
```

### nginx操作

```C
sudo apt install nginx                                   //安装nginx
sudo nginx -t                                            //验证nginx安装
sudo vim /etc/nginx/sites-enabled/default                //编辑配置文件
root /home/ubuntu/code/myblog/public;                    //设置网站根目录
sudo service nginx start                                 //启动Ngnix
sudo service nginx stop                                  //停止Ngnix
sudo service nginx restart                               //重启Ngnix
```

### hexo操作

```C
hexo g / generate                                        //生成静态文件
hexo s / server                                          //在本地服务器运行
hexo clean                                               //清除缓存
hexo new article                                         //新建文章(source/_posts/artical.md)
```
