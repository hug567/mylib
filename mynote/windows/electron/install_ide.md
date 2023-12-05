# win10安装electron开发环境：

## 1、node.js：

```bash
# 网站：
https://nodejs.org/en/download/
# 64位安装包：
https://nodejs.org/dist/v20.10.0/node-v20.10.0-win-x64.zip
# 下载后解压，并将路径加入系统路径：
"此电脑"右键 -> 属性 -> 高级系统设置 -> 环境变量 -> Path -> 编辑 -> 新建
# 设置成后cmd查看安装信息：
node -v
npm -v
# 设置国内npm镜像源：
npm config set registry "https://registry.npm.taobao.org/"
# 查看镜像源：
npm config get registry
```

## 2、electron：

```bash
# 独立安装：官方推荐在app工程所在目录安装，可以保持每个app有一个独立的electron开发环境
npm install --save-dev electron
# 全局安装：（指定taobao源）
npm install -g electron --registry=https://registry.npm.taobao.org
# 查看版本：
electron -v
```

- 运行electron-quick-start：

```bash
# 下载：
git clone https://github.com/electron/electron-quick-start.git
# 运行：
cd electron-quick-start
electron ./
```

