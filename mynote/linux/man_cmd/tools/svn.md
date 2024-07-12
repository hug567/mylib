# 1、安装：

```bash
sudo apt install subversion
```

# 2、常用命令：

```bash
suv
    --help                       # 查看帮助
```

# 3、常见用法：

```bash
# checkout目录
mkdir svn_repo
cd svn_repo
# 路径中有空格时，用单引号括住链接地址
svn checkout http://192.168.99.221:8080/xxx
```