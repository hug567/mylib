# Ubuntu服务器部署Hexo博客

## 1、安装nginx：

```C
sudo apt install nginx                                   //安装软件
nginx -v                                                 //查看nginx版本
sudo nginx -t                                            //验证nginx安装
/* 浏览器打开服务器ip： */
http://192.168.1.27/

/* 修改网站根目录： */
sudo vim /etc/nginx/sites-enabled/default                //打开配置文件
root /home/hx/nginx;                    //设置网站根目录

/* 重启nginx： */
sudo service nginx start                                 //启动Ngnix
sudo service nginx stop                                  //停止Ngnix
sudo service nginx restart                               //重启Ngnix

```

## 2、安装hexo：

```c
sudo apt install nodejs npm                              //安装nodejs和npm
node -v                                                  //查看node版本
npm -v                                                   //查看npm版本
sudo npm install n -g                                    //安装更新版本工具N
sudo n stable                                            //更新nodejs版本
npm ls --depth 0                                         //查看已安装的hexo插件
sudo npm install -g hexo                                 //安装hexo
sudo npm install -g hexo-cli                             //安装hexo插件
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
## 3、创建hexo博客：

```shell
mkdir hexo                                               # 创建目录
cd hexo                                                  # 进入目录
hexo init                                                # hexo初始化
hexo g / generate                                        # 生成静态文件
hexo s / server                                          # 在本地服务器运行
hexo d / deploy                                          # 部署博客
hexo clean                                               # 清除缓存
hexo new article                                         # 新建文章(source/_posts/artical.md)
cp -r public/* ~/nginx                                   # 拷贝文件到网页目录

sudo npm install

/* 下载主题并复制至theme目录： */
https://hexo.io/themes/
/* 配置博客主题： */
vim _config.yml
theme: syefe
```

## 附录：常见报错

### 1）、hexo -v报错：
```shell
# 报错：
 $ hexo -v
console.js:35
    throw new TypeError('Console expects a writable stream instance');

# 解决：升级node到hexo期望的最低版本
# hexo-cli: v4.2.0
# node: >=v10.13.0
wget https://npm.taobao.org/mirrors/node/v10.13.0/node-v10.13.0-linux-x64.tar.xz
tar -xvf node-v10.13.0-linux-x64.tar.xz
cd /usr/local/bin
sudo ln -s /home/hx/tools/node-v10.13.0-linux-x64/bin/node node
node -v
```


