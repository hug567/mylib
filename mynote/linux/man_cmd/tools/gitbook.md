# 1、安装：
## 1）、ubuntu 18.04：

```bash
# ubuntu 18.04
sudo apt install nodejs npm
npm config set registry https://mirrors.cloud.tencent.com/npm/
npm cache clean --force
sudo npm install -g gitbook-cli
gitbook -V

# 查看gitbook版本：
gitbook --version
# 空目录中创建gitbook
gitbook init
# 查看预览
gitbook serve

# 卸载
sudo npm uninstall -g gitbook-cli
# npm查看registry
npm config get registry
```

## 2）、ubuntu 22.04：

```bash
# 源码安装node：
wget https://nodejs.org/download/release/v10.24.1/node-v10.24.1.tar.gz
tar -xvf node-v10.24.1.tar.gz
cd node-v10.24.1
./configure --prefix=/usr
make -j
# 安装：
sudo make install
# 卸载：
sudo make unstall
# 验证：
node -v
npm -v

# 安装gitbook：
npm config set registry https://mirrors.cloud.tencent.com/npm/
npm cache clean --force
sudo npm install -g gitbook-cli
gitbook -V
```

# 2、创建book：

```bash
gitbook init testbook
cd testbook
gitbook serve
# 访问：
http://10.110.0.3:4000
# 指定端口：
 gitbook serve --port 9010
 # 生成静态网页：
 gitbook build --output=/tmp/gitbook
```

