## 1、安装git：

```C
sudo apt install git                                     //安装git
git --version                                            //查看git版本
git config --global user.name "Huang Xing"               //设置用户名
git config --global user.email huangxing567@163.com      //设置邮箱

ssh-keygen -t rsa -C "huangxing567@163.com"              //配置SSH Key
cat ~/.ssh/id_rsa.pub                                    //查看SSH Key

git config --global credential.helper store              //长期缓存账号密码
```

### 1.1）、使用代理下载：

```bash
# 下载代码时使用代理：
git clone -c http.proxy="http://127.0.0.1:10809" https://github.com/transcode-open/apt-cyg.git
```
### 1.2）、下载大体积仓库：

```bash
# 当仓库提交历史记录太多导致直接下载容易失败时，可使用如下方法：
# 先在clone时指定深度为1，只下载最新的一个commit：
git clone https://github.com/wolfSSL/wolfssl.git --depth=1 ./
# 再使用fetch逐步拉取所有commit：
git fetch --depth=1000
git fetch --depth=2000
git fetch --depth=3000
...
# 最后去除深度限制再fetch一次：
git fetch --unshallow

# 只克隆不检出，深度1，只拉取一个分支
git clone --no-checkout --depth=1 --single-branch --branch master https://github.com/RT-Thread/rt-thread.git
# 待测试环境变量：
# GIT_HTTP_LOW_SPEED_LIMIT：最低传输速度（字节/秒）
# GIT_HTTP_LOW_SPEED_TIME：如果传输速度低于 GIT_HTTP_LOW_SPEED_LIMIT 并持续指定时间（秒），则中止操作

# 查看本地仓库深度：
git log --oneline | wc -l
```

## 2、常用操作：

### 2.1、查看状态

```C
git log                                                  //查看提交日志
git log --name-status                                    //log显示修改/新增文件列表
git log --stat                                           //查看commit修改行数
git show                                                 //查看最新commit详细修改
git show <commitID>                                      //查看指定commit详细修改
git show <commitID> <filename>                           //查看指定commit中某个文件详细修改
git tag                                                  //查看所有tag
git diff --stat                                          //查看diff的修改行数
/* 统计提交代码 */
git log --author="Huang Xing" --pretty=tformat: --numstat | gawk \
'{ add += $1: subs += $2: loc += $1 - $2} END \
{printf "added lines: %s removed lines: %s total lines: %s\n", add, subs, loc }' -
/* 查看详细commit信息 */
git log --oneline --graph --pretty=format:'%C(yellow)%h %Cred[%an]%Creset %Cblue[%ad]%Creset %s %Cgreen(%cr)%Cred%d' --date=format:'%Y-%m-%d %H:%M:%S' -n 100
/* 指定文件最近一次提交时间 */
git log --pretty=format:"%cd" --date=format:"%Y-%m-%d %H:%M:%S" -1 main.c
/* 指定文件最早一次提交时间 */
git log --pretty=format:"%cd" --date=format:"%Y-%m-%d %H:%M:%S" main.c | tail -1
/* 指定文件最近一次提交年份 */
git log --pretty=format:"%cd" --date=format:"%Y" -1 main.c
/* 指定文件倒序提交时间 */
git log --pretty=format:"%cd" --date=format:"%Y-%m-%d %H:%M:%S" --reverse main.c

//查看忽略的文件
git status --ignored
//查看仓库顶层目录
git rev-parse --show-toplevel

//从远端拉取更新到本地
git fetch -p
//从远端拉取更新到本地时指定remote
git fetch <remote>
//只拉取特定分支
git fetch <remote> <branch>
//拉取所有tag
git fetch -t
```

### 2.2、本地分支管理

```C
git branch                                               //查看本地所有分支
git branch -vv                                           //查看本地分支关联的远端分支
git branch dev --set-upstream-to=origin/dev              //设置本地分支关联远端分支
git branch -a                                            //查看本地和远端所有分支
git branch dev                                           //切换本地分支
git branch -d dev                                        //删除本地分支
git branch -D dev                                        //强制删除本地分支
git branch -m <newname>                                  //重命名当前分支
git branch -c <newname>                                  //复制当前分支
//----------checkout-------------------------------------------------------//
git checkout -b dev                                      //新建并切换分支
git checkout dev                                         //新建本地分支
git checkout -b dev origin/dev                           //新建本地分支并追踪远端
git merge dev                                            //合并本地分支dev至当前分支
//----------取回远端分支-----------------------------------------------------//
git fetch origin master                                  //取回远端master分支至本地
git log -p FETCH_HEAD                                    //查看取回的更新信息
git diff master origin/master                            //比较本地分支与远端分支
git rebase master                                        //线性合并取回的远端分支至当前分支
//----------不提交commit切换分支---------------------------------------------//
git stash                                                //暂存未add更改
git stash list                                           //查看暂存列表
git chechout <branch2>                                   //切换分支
git stash pop                                            //取出暂存
git stash drop stash@{0}                                 //删除stash第一个队列
git stash clear                                          //清空stash所有内容

git remote prune origin                                  //删除远端已删除本地仍存在的分支
git gc                                                   //清理不必要的文件并优化本地存储库
git prune                                                //从对象数据库中删除所有不可访问的对象
```

### 2.3、远端分支管理

```C
git push origin HEAD:master                              //推送本地分支至远端
git push origin HEAD:master -f                           //强制推送本地分支至远端
git branch -r                                            //查看所有远端分支
git push --delete origin <branch>                        //删除远端分支
git push --all origin                                    //本地所有分支都推送到远端origin

//----------重命名远端分支-------------------------------------------------//
git push --delete origin <branch>                        //删除远端分支
git branch -m <newname>                                  //重命名本地分支
git push origin HEAD:<newname>                           //提送至远端分支

/* -------- 远端仓库管理 ------------------------------------------------- */
git remote -v                                            //查看远程仓库地址
/* 设置添加远程仓库地址： */
git remote set-url <origin> <https://gitee.com/...>      //更新远端地址
git remote add <github> <https://github.com/...>         //添加远端
git remote remove <gitee>                                //删除远端
git remote rename <gitee> <origin>                       //重命名远端
/* 验证连接远程仓库地址： */
ssh -T git@github.com
/* 推动至远端： */
git push origin HEAD:master                              //推送至origin(gitee)
git push github HEAD:master                              //推送至github

// 添加本地仓库为远端
git remote add local /home/hx/code/linux-5.10
// 查看分支作者
git for-each-ref --format='%(committerdate) %09 %(authorname) %09 %(refname)' | sort -k5n -k2M -k3n -k4n

//仓库commit太多，如linux截至2014-10-18有1309687条commit，分批次推送到远端：
//先推送最开始的100000条：
git log --oneline | tail -n 100000 | head -n 1
//将commit推送到远端分支
git push origin <commit ID>:refs/heads/master
//后续可以此类推

//拉取远端指定分支到本地
git pull origin <origin_branch>:<local_branch>
```

### 2.4、commit操作

```C
git cherry-pick <commit-id>                              //挑选提交指定commit
git commit -s                                            //提交信息中附上Singed-off-by
git commit -m "message"                                  //提交commit及标题
git commit -a                                            //不用add提交commit

//----------合并至最近一次commit-------------------------------------------//
git add <file>                                           //添加文件
git commit --amend                                       //追加至最新commit
git commit --amend --no-edit                             //不修改commit描述
git commit --amend -m "message"                          //合并的同时修改commit描述

//----------合并至指定commit----------------------------------------------//
git stash                                                //暂存
git log --oneline                                        //查看指定commit的ID
git rebase -i <ID>^                                      //移动HEAD至指定ccommit
git rebase -i HEAD~5                                     //移动HEAD至指定ccommit
/* 首行pick改为e，保存并推出 */                          //编辑
git stash pop                                            //取出暂存
git add <file>                                           //添加文件
git commit --amend                                       //追加至指定commit
git rebase --continue                                    //移动HEAD至最新commit
/* 如果有冲突，坚决冲突后 */                                 //如果有冲突
    git add <file>                                       //添加文件
    git commit --amend                                   //追加至指定commit
    git rebase --continue                                //移动HEAD至最新commit

//----------合并几个commit------------------------------------------------//
git log --oneline                                        //查看最早需要合并的commit ID
git rebase -i <ID>^                                      //定位至最早需要合并的commit
/* 首行pick不动，下面需要被合并的commit将pick改为s，:wq */
/* 修改commit message，若有冲突则解决冲去，:wq */

//----------调整commit顺序------------------------------------------------//
git rebase -i HEAD~<n>                                   //定位至最前一条commit
/* 调整commit顺序后，:wq报错退出 */

//----------cherry-pick另一个仓库的commit----------------------------------//
git remote add repo2 .../path/to/repo2                     //添加另一个本地仓库
git remote add repo2 https://gitee.com/hug567/mylib.git    //添加另一个远端仓库
git fetch repo2                                            //拉取仓库
git cherry-pick <Commit ID>                                //pick另一仓库commit

//----------拆分commit---------------------------------------------------//
//拆分第1个commit
git reset --mixed HEAD~
git add <files>
git commit -s

//拆分第2个commit
git rebase -i HEAD~2
  pick -> e
git reset --mixed HEAD~
git add <file1> ...
git commit -s
git add <file2> ...
git commit -s
git rebase --continue

//git添加commit指定作者
git commit -s --author="Huang Xing <huangxing567@163.com>"
//已提交的commit修改作者
git commit --amend --author="Huang Xing <huangxing567@163.com>"

//git添加空目录：在空目录中创建.gitkeep文件后创建commit
touch .gitkeep
git add .
git commit -s "Add empty folder"
```

### 2.5、撤销操作

```C
//----------撤销更改------------------------------------------------------//
git reset --mixed HEAD^                        //撤销最近一条commit，撤销add
git reset --mixed ea00ac6^                     //撤销指定commit以来所有的提交，撤销add
git reset --soft HEAD                          //撤销最近一条commit，不撤销add
git reset --hard HEAD~1                        //删除最近一条commit
git reset HEAD                                 //撤销当前所有文件add
git reset HEAD <file>                          //撤销当前指定文件的add
/* 回退至指定commit： */
git log --before="2019-7-1"                    //查看指定日期前的提交
git log --before "2020-05-04" --oneline --pretty="%h %ad %s %cr" --date=format:"[%Y-%m-%d %H:%M:%S]"
git reset --hard <commit id>                   //回退至指定commit（该commit保留）

git checkout .                                 //删除所有未add更改
git chechoout <file>                           //删除指定文件未add更改

//----------删除指定commit-----------------------------------------------//
git rebase -i <ID>^                            //定位至需要删除的commit
/* 将需删除的commit的pick改为d，:wq */

//----------删除未追踪文件-------------------------------------------------//
git clean -nf                                  //查看将被删除未追踪的文件
git clean -nfd                                 //查看将被删除未追踪的文件及目录
git clean -nfdx                                //查看将被删除未追踪与.gitignore忽略的文件及目录
git clean -f                                   //删除未追踪的文件
git clean -fd                                  //删除未追踪的文件及目录
git clean -fdx                                 //删除未追踪与.gitignore忽略的文件及目录

//撤销第1个commit中指定文件的提交，文件的修改还在，git status可查看
git reset HEAD^ <files>
git reset HEAD~1 <files>
git commit --amend / git commit --amend --no-edit

//撤销第2个commit中指定文件的修改
git reset HEAD~2 <files>
git reset <commit ID>~ <files>
git checkout <files>
git stash
git rebase HEAD~2
git rebase <commit ID>~
pick -> e
git stash pop
git add <files>
git commit --amend
git rebase --continue

git revert HEAD                                //撤销最近一次提交
git revert <commit>                            //撤销指定commit提交
```

### 2.6、查看差异：

```bash
# 查看当前修改差异
git diff
# 查看已add但未commit的差异
git diff --cached
git diff --staged
# 查看两个分支间的差异
git diff <branch1> <branch2>
# 查看两个分支文件上的差异
git diff --stat <branch1> <branch2>
# 查看当前修改与指定分支的差异
git diff <branch2>
# 查看当前修改与指定分支上指定文件的差异
git diff <branch2> <file>
# 查看两个tag指定文件的差异
git diff <v0.0.1> <v0.0.2> <default.xml>
```

### 2.7、合并分支：

```bash
# 切换至目标分支main
git co main
# 合并开发分支dev
git merge dev
```

### 2.8、设置忽略

```c
.gitignore                                     //会被提交至git仓库
.git/info/exclude                              //本地设置，不会被提交至git仓库

//设置举例：
*.swp
cscope.*
/vmlinux
!.gitignore
/arch/*/include/generated/

//忽略某个目录下的所有指定类型文件
/subdir/**/*.elf

//忽略已提交的文件
git rm <file>
vim .gitignore
git add .gitignore  //设置忽略文件
git commit -m "Delete and ignore files"
```

### 2.9、stash暂存

```c
git stash save "title"                         //自定义stash标题
git stash -h                                   //查看stash帮助
git stash -u                                   //暂存未追踪的文件
git stash list                                 //查看stash列表
git stash show                                 //查看最新stash差异
git stash show -p                              //查看最新stash详细修改
git stash show -p <id>                         //查看指定id的stash详细修改
git stash pop stash@{1}                        //恢复指定暂存
git stash drop                                 //删除所有暂存
git stash drop stash@{1}                       //删除指定暂存
git stash push <file>...                       //暂存指定文件
git stash push -m "message" <file>...          //暂存指定文件并自定义message
//修改指定暂存名称：先删除指定暂存，再添加
git stash drop stash@{1}
git stash store -m "New message" af8fdeee49a03d1b4609f294635e7f0d622e03db
```

### 2.10、patch操作：

```shell
# 制作patch
git format-patch -1                              # 最新一个commit生产patch
git format-patch -1 <ID>                         # 指定commit生成patch
git format-patch <ID>                            # 生成指定commit以来的patch (不包含该patch)
git format-patch <ID1>...<ID2>                   # 生成两个commit之间的patch (包含两个commit)

# 应用patch
git apply --check <patch>                        # 检查patch是否有冲突
git am <patch>                                   # 应用patch
git am --abort                                   # 撤销应用patch
```

### 2.11、tag操作：

```bash
# 查看所有tag
git tag
# 通配符查看一系列tag
git tag -l "v1.8.5*"
# 创建标签
git tag v1.4
# 创建tag时写message，会保存tag的创建时间
git tag -a v1.4 -m "my version 1.4"
# 推送标签到远端
git push origin v1.4
# 删除标签
git tag -d v1.4
# 删除远端仓库中的标签
git push origin :refs/tags/v1.4

# 创建tag并签名：----------------------------------#
# 生成gpg key：
gpg --full-generate-key
#------------------------------------------------#
(1) RSA and RSA (default)
0 = key does not expire
Is this correct? (y/N) y
Real name: HuangXing
Email address: huangxing@rhosoon.com
Comment:
Change (N)ame, (C)omment, (E)mail or (O)kay/(Q)uit? O
Passphrase: xxx  # 需要连续输入两次
# gpg: revocation certificate stored as '/home/hx/.gnupg/openpgp-revocs.d/D64BF234D1861EF0718B367A4ACA75DC99B1ADE9.rev'
#------------------------------------------------#
# 查看生成的private key：
gpg --list-secret-keys --keyid-format=long
# 查看生成的public key：（需要src行rsa4096后面的字符串(16个字符)：4A************E9）
gpg --list-keys --keyid-format=long
# 导出gpg public key，可设置到git网站中：
gpg --armor --export 4A************E9
# git设置gpg key：
git config --global user.signingkey 4A************E9
# 设置环境变量：
export GPG_TTY=$(tty)
# 给tag签名，也可给commit签名：
git tag -s v2.35 -m "Add new tag v2.35"
# 查看tag的签名：
git tag -v v2.35
```

### 2.12、submodule：

```bash
# 查看当前仓单的子仓库：
git submodule
# 查看当前仓单的子仓库的配置：
cat .gitmodules
# 递归查看当前目录下所有仓单的子仓库：
git submodule status --recursive
# 查看帮助：
git submodule --help

# 在下载仓库的同时下载子模块：
git clone --recurse-submodules <repository_url>

# 已下载主仓库但没有下载子仓库：
# 初始化并拉取子仓库：
git submodule update --init --recursive

# 已有子仓，拉取子仓库的更新：
git submodule update --recursive --remote

# 只更新指定子仓库：(在.gitmodules文件中可查看子仓库路径)
git submodule update --init --remote FreeRTOS-Plus/ThirdParty/wolfSSL
```

## 3、git lfs：

```bash
# ubuntu 16.04
curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash
sudo apt install git-lfs
# ubuntu 20.04/22.04
sudo apt install git-lfs
git lfs --version

git lfs pull                                            # 拉取文件
git lfs track <file>                                    # 追踪文件
git lfs untrack <file>                                  # 取消追踪文件
git lfs ls-files                                        # 显示追踪文件列表
git lfs status                                          # 查看lfs追踪的文件状态

# 提交文件，与普通文件提交相同
git add <files>
git commit
git push origin HEAD:branch

# 追踪已普通提交的二进制文件
git lfs track <files>
git lfs migrate import --no-rewrite <files> -m "lfs track"

# 使用了git lfs的仓库迁移到新地址
git clone --bare https://gitlab.rhosoon.com:9003/zynq7020/yocto.git
cd yocto.git
git lfs fetch --all
git remote add gitea http://192.168.99.221:3000/Rhosoon_RD/yocto.git
git lfs push --all gitea
git push --mirror gitea

# 取消已追踪的文件，改为提交为普通文件
git lfs pull
git lfs ls-files
git lfs prune
git lfs untrack <file>
git status
git add .
git commit -m "Untrack files"
```

## 4、tig：

```c
sudo apt install tig                         //安装tig

Enter                                        //右侧展开commit详情视图

Up / Down                                    //左侧选中不同commit
J / K                                        //左侧选中不同commit
j / k                                        //右侧commit详情中上下移动光标
PageUp / PageDown                            //右侧commit详情上下翻页
d                                            //全屏显示commit详情

q                                            //后退一个视图
m                                            //回到主视图
l                                            //查看log，同：git log --name-status
h                                            //显示帮助

/* 配置文件：~/.tigrc */
# 颜色设置：color area fgcolor bgcolor [attributes]

# 中间分隔线颜色
color title-blur blue default

# 底部聚焦栏颜色 (237:灰)
color title-focus blue 237

# 当前行颜色 (235:黑, 228:黄)
color cursor 235 228
```
