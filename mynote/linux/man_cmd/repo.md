# 1、repo安装：

```bash
cd ~/tools
git clone https://gerrit-googlesource.proxy.ustclug.org/git-repo/
export PATH="$HOME/tools/git-repo:$PATH"
repo --version
```

# 2、repo基本用法：

```bash
# 使用远端manifest仓库
repo init -u https://gitee.com/hug567/manifest
# 使用本地manifest仓库
repo init -u /home/hx/code/manifest
# 同步代码
repo sync
```

# 3、repo常用命令：

```bash
repo --help
repo help <cmd>
repo status
repo branches
repo diff
```

