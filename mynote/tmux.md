## 1、安装tmux：

```c
sudo apt install tmux                    //安装tmux
tmux -V                                  //查看tmux版本
Ctrl + B                                 //默认Prefix
```

## 2、会话操作(session)：

```c
tmux new                                 //新建会话
tmux new -s <name>                       //制定名称新建会话
tmux kill-session -t <name>              //删除指定会话
tmux kill-server                         //删除所有会话
tmux ls                                  //列出所有会话
tmux a                                   //恢复默认会话
tmux a -t <name>                         //恢复指定会话
Prefix + s                               //切换会话
Prefix + d                               //断开会话
Prefix、Shift + $                        //重命名会话
```

## 3、窗口操作(window)：

```c
Prefix + c                               //新建窗口
Prefix + n                               //跳转至第n个窗口
Prefix + q                               //自定义退出窗口(默认：Prefix + &)
Prefix + w                               //列出所有窗口
Prefix + f                               //搜索窗口
Prefix + ,                               //重命名当前窗口
tmux swap-window -s 3 -t 1               //交换3号和1号窗口
tmux swap-window -t 1                    //交换当前和1号窗口
tmux move-window -t 1                    //移动当前窗口至1号
```

## 4、窗格操作(pane)：

```c
tmux move-window -t 1                    //移动当前窗口至1号
Prefix + \                               //自定义垂直分割窗格(默认：Prefix + %)
Prefix + -                               //自定义水平分割窗格(默认：Prefix + ”)
Prefix + q                               //自定义关闭窗格(默认：Prefix + x + y)
Prefix + o                               //切换窗格
Prefix + !                               //当前窗格切换至新窗口
Prefix + { / }                           //窗格切换位置
Prefix + PageUp / PageDown               //上下翻页
q                                        //退出翻页
Prefix, Alt + 方向键                     //缩放窗格
```

## 5、文本复制粘贴：

```C
Prefix + [                               //进入复制模式
空格键                                   //开始复制
方向键                                   //选中文本
Enter                                    //复制完成并退出
Prefix + ]                               //粘贴
^ / 0                                    //跳至行首
$                                        //跳至行尾
V                                        //选择行
h                                        //光标向左
j                                        //光标向下
k                                        //光标向上
l                                        //光标向右
```

## 6、tmux支持256色：

```c
//在~/.bashrc, ~/.zshrc中添加以下内容并source
alias tmux='tmux -2'
export TREM=xterm-256color
//在~/.tmux.conf中添加以下配置


```

## 7、Windows下Git Bash安装tmux：

```c
//下载tmux：https://github.com/xnng/my-git-bash/tree/master/tmux
//将bin目录下所有文件复制到： C：\Program Files\Git\usr\bin
//将share目录下所有文件复制到： C：\Program Files\Git\usr\share
```
