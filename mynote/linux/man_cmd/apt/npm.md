# 1、常用命令：

```bash
sudo apt instll npm

npm
	-v                                  # 查看版本
```

# 2、日常使用：

## 1）、常见用法：

```bash
npm install -g <package>
npm uninstall -g <package>
npm config set registry https://mirrors.cloud.tencent.com/npm/
npm config get registry
```

## 2）、离线安装npm包：

```bash
# 在联网的机器上安装npm包：
mkdir dir_npm
cd dir_npm
npm install nmp-bundle
npm install ep_align
./node_modules/.bin/npm-bundle ep_align
# 拷贝到内网机器上：
scp ep_align-0.3.96.tgz user@192.168.0.13:~
# 在内网机器中离线安装npm包：
sudo npm install ./ep_align-0.3.96.tgz -g
```

