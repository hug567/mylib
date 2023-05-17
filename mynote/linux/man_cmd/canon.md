# 1、常见命令：

```bash
# 安装
sudo pip install canon

# 查看帮助
conan -h
```

## 1）、remote：

```bash
# 查看remote命令帮助
conan remote -h
# 列出所有远端
conan remote list
# 添加远端仓库
conan remote add conan-transit https://conan-transit.bintray.com
```

## 2）、search：

```bash
# 查看search帮助
conan search -h
# 在远端仓库conancenter中搜索包glog
conan search <glog> --remote <conancenter>
```

## 3）、install：

```bash
# 查看install帮助
conan install -h
```

## 4）、remove：

```bash
# 查看remove帮助
conan remove -h
```

