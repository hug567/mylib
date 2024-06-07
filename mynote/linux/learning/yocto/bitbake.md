# 1、bitbake：

## 1）、基本用法：

```bash
bitbake <target>                             # 执行指定target的所有任务
bitbake -c <task> <target>                   # 执行指定target的指定任务
bitbake -c do_configure <target>             # 执行指定target的do_configure任务
bitbake -c clean <target>                    # 清除指定target的所有输出文件
bitbake -c cleansstate <target>              # 清除指定target的所有输出文件和共享状态缓存
bitbake -c cleanall <target>                 # 清除指定target的所有输出文件、共享状态缓存和下载的源文件
bitbake -c listtasks <target>                # 显示指定target的可执行任务
bitbake -s                                   # 显示所有可执行的包
bitbake -e <target>                          # 显示指定target当前执行环境
bitbake -g <target>                          # 显示指定任务的所有依赖，保存在文件task-depends.dot中
	sudo apt install graphviz                    # 查看图形化的依赖关系
	dot -Tpng task-depends.dot -o task-depends.png
bitbake -b <xx.bb>                           # 直接执行指定bb文件
bitbake -v <target>                          # 打印一些调试信息
bitbake -vDDD <target>                       # 打印一些调试信息，可以跟多个D

# 获取指定recipe将要执行的所有代码
bitbake -e device-tree > device-tree.py
# 搜索特定任务关键字，如：
"do_fetch ()"
"do_configure()"

# 修改tmp/work-shared/qemuarm64/kernel-source中的代码后重新编译linux
bitbake -C compile linux-yocto               # 推荐使用
bitbake -f -c compile linux-yocto
```
# 2、bitbake-layers：

## 1）、常见用法：

```bash
# 查看所有layer
bitbake-layer show-layers
# 查看所有recipe
bitbake-layer show-recipes
# 查看所有带bbappend的recipe的bb和bbappend文件
bitbake-layer show-appends
```

## 2）、创建layer：

```bash
# 创建layer
cd poky
source oe-init-build-env    # 自动进入了build目录
cd ..                       # 推出build目录，进入上一级目录
bitbake-layers create-layer meta-qemu
# 添加layer
bitbake-layers add-layer meta-qemu

# 查看使能的layer
bitbake-layers show-layers
```

