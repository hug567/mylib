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
# 删除远端
conan remote remove <xxx>
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

## 5）、new：

```bash
# 查看new帮助
conan new -h
# 新家一个conan工程
conan new -d name=hello -d version=1.0.0 cmake_exe
```

## 6）、create：

```bash
# 查看create帮助
conan create -h
# 构建项目
conan create <.../path/to/conanfile.py>
```

## 7）、profile：

```bash
# 查看profile帮助
conan profile -h
# 生成profile
conan profile detect
# 列出所有profile
conan profile list
# 显示profile文件路径
conan profile path <default>
# 显示show帮助
conan profile show -h
# 显示profile文件内容
conan profile show
```

## 8）、list：

```bash
# 查看帮助
conan list -h
conan list <hello>
```

