## 1、安装tmux：

```c
sudo apt install tmux                    //安装tmux
tmux -V                                  //查看tmux版本
Ctrl + B                                 //默认Prefix键

tmux show-options -g | grep prefix      //tmux查看prefix键
set -g prefix C-b                       //设置prefix键为Ctrl+b
set -g prefix2 C-b                      //设置prefix2键为Ctrl+b
unbind C-a                              //取消快捷键C-a
bind C-b send-prefix                    //设置prefix键为Ctrl+b
```

## 2、会话操作(session)：

```c
tmux new                                 //新建会话
tmux new -s <name>                       //指定名称新建会话
tmux kill-session -t <name>              //删除指定会话
tmux kill-server                         //删除所有会话
tmux ls                                  //列出所有会话
tmux a                                   //恢复最新创建的会话
tmux a -t <name>                         //恢复指定会话
Prefix + s                               //切换会话
Prefix + d                               //脱离当前会话
tmux detach-client                       //脱离当前会话
tmux detach-client -s hx                 //脱离指定会话
tmux detach-client -a                    //脱离所有会话
Prefix, Shift + $                        //修改会话名
```

## 3、窗口操作(window)：

```c
Prefix + c                               //新建窗口
Prefix + n                               //跳转至第n个窗口
Prefix + q                               //自定义退出窗口(默认：Prefix + &)
Prefix + w                               //列出所有窗口
Prefix + f                               //搜索窗口
Prefix + ,                               //修改窗口名
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
Prefix, Alt+方向键                        //缩放窗格
Prefix, Alt+5                            //均匀分布窗格

/*----- ~/.tmux.conf -----*/
bind ` send-prefix                       //按两次prefix输入`键
bind u display-pane                      //自定义命令显示窗格编号 (Prefix + u)

tmux swap-pane -s 2 -t 1                 //交换窗格
```

## 5、文本复制粘贴：

```C
Prefix + [                               //进入复制模式
  空格键                                    //开始复制
  方向键                                    //选中文本
  Enter                                    //复制完成并退出
Prefix + ]                               //粘贴
^ / 0                                    //跳至行首
$                                        //跳至行尾
V                                        //选择行
h                                        //光标向左
j                                        //光标向下
k                                        //光标向上
l                                        //光标向右

tmux capture-pane -S -                   //保存当前窗格中所有历史到buffer
tmux capture-pane -S - -t 1              //保存指定窗格中所有历史到buffer [-t target-pane]
Prefix + PageUp                          //查看当前窗格行数，右上角现实的是当前行的倒数行数与总行数
tmux capture-pane -S -351                //保存当前窗格中倒数指定行到buffer
tmux save-buffer output.log              //buffer内容保存到文件
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

## 8、tmux插件：

```bash
# tmux插件
https://github.com/tmux-plugins/tpm
https://github.com/tmux-plugins/tmux-resurrect

# tmux-resurrect
Prefix, Ctrl + S        # 保存会话
Prefix, Ctrl + R        # 恢复会话
```
