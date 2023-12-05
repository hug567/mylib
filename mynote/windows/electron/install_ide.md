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
```

## 2、electron：

```bash
# 独立安装：官方推荐在app工程所在目录安装，可以保持每个app有一个独立的electron开发环境
npm install --save-dev electron
# 全局安装：
npm install electron -g
```

