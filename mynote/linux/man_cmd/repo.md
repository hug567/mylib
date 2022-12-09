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
repo help                                   # 查看支持的命令
repo help <cmd>                             # 查看命令详细帮助
repo list                                   # 列举仓库
repo info                                   # 查看仓库信息
repo sync                                   # 同步代码
#    git remote update
#    git rebase origin/branch
repo start <branch> <--all/project>         # 切换分支
#    git checkout -b <branch>
repo branches                               # 查看所有仓库分支
repo checkout <branch>                      # 切换至本地分支
repo diff                                   # 查看代码修改对比
repo status                                 # 查看仓库状态
repo abandon <branch>                       # 删除所有仓库分支
#    git branch -D
repo stage -i                               # 添加文件至暂存区
#    git add --interactive
repo prune                                  # 删除已合并分支
#    git branch -d
repo forall -c <shell cmd>                  # 在所有仓库中执行制定shell命令
    -c    # 指定shell命令
    -p    # 显示仓库名称
    -v    # 显示shell命令错误信息

# 更改默认分支
repo init -m top.xml -b <branch>
repo sync
```
