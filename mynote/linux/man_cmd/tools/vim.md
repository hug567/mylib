## 1、常用功能：

### 1）、进入编辑模式：

```c
i                                //进入编辑模式，光标不动
a                                //进入编辑模式，光标向后跳一个字符
o                                //进入编辑模式，光标下插入空行
s                                //进入编辑模式，并删除光标后一个字符
I                                //进入编辑模式，光标跳至行首
A                                //进入编辑模式，光标调至行尾
O                                //进入编辑模式，光标上插入空行
Ctrl + S                         //锁定屏幕
Ctrl + Q                         //解锁屏幕
:e                               //重新加载文件
vim file.txt +100                //打开文件并定位到指定行
```

### 2）、常规模式文本编辑：

```c
x                                //删除光标后一个字符，同Delete
X                                //删除光标前一个字符，同Backspace
nx                               //向后删除n个字符
nX                               //向前删除n个字符
yy                               //复制光标所在行
ny                               //复制光标所在行
nyy                              //复制光标所在行向下n行
p                                //从光标下一行开始粘贴
%                                //跳转至匹配括号
dd                               //剪切光标所在行
ndd                              //剪切光标所在行向下n行
u                                //撤销
Ctrl + R                         //恢复
v                                //进入VISUAL模式
hjkl                             //左下上右选中文本，同方向键
^ / HOME                         //选中光标至行首
$ / END                          //选中光标至行尾
d                                //剪切
y                                //复制
p                                //粘贴
^ / HOME                         //选中光标至行首
$ / END                          //选中光标至行尾
ggyG                             //全部复制进默认寄存器
:n1,n2d                          //删除n1-n2行内容
```

### 3）、跳转翻页：

```c
gg                               //光标移到至第一行
G                                //光标移动至最后一行
nG                               //光标移动至第n行
nEnter                           //光标向下移动n行
Ctrl + e                         //屏幕向上翻页一行
Ctrl + y                         //屏幕向下翻页一行
```

### 4）、显示分屏：

```c
:sp                              //横向分屏
:vs                              //竖向分屏
ctrl + w   w                     //各窗口循环跳转
ctrl + w   h                     //跳转至左侧窗口
ctrl + w   j                     //跳转至下方窗口
ctrl + w   k                     //跳转至上方窗口
ctrl + w   l                     //跳转至右侧窗口
ctrl + w   <                     //窗口向左缩放
ctrl + w   >                     //窗口向右缩放
ctrl + w   +                     //窗口向上缩缩
ctrl + w   -                     //窗口向下缩放
10, ctrl + w   <                 //窗口向左缩放10列
10, ctrl + w   >                 //窗口向右缩放10列
10, ctrl + w   +                 //窗口向上缩缩10行
10, ctrl + w   -                 //窗口向下缩放10行
ctrl + w   =                     //窗口尺寸恢复均等
```

### 5）、跨进程复制：

```c
vim --version | grep "clipboard"     //查看是否支持系统剪切板
sudo apt-get install vim-gnome       //安装图像化vim
v                                    //进入VISUAL模式，方向键选中
"+y                                  //复制进“+”寄存器
"+yG                                 //全文复制进“+”寄存器
"+p                                  //从“+”寄存器粘贴
:reg                                 //查看寄存器内容
```

### 6）、搜索替换：

```C
/word                                //向光标之下搜索
?word                                //向光标之上搜索
/word\c                              //大小写不敏感
/[\ux]                               //搜索ASCII值，x为十六进制数
n/N                                  //向下/上查找匹配
:n1,n2s/word1/word2/g                //在n1至n2行间将word1替换为word2
:n1,n2s/word1/word2/gc               //替换前需确认
:%s/word1/word2/gc                   //全局搜索替换
shift + *                            //搜索单词
.*\[]^$                              //需转移字符
:%s/^M//gc                           //搜索替换dos换行符，^M使用 Ctrl+V+Enter 输入
:%s/;.\+$//gc                        //搜索指定字符至行尾
:%s/字符串//ng                        //统计字符串在当前文件中的个数
:%s/^\s*$\n//gc                      //删除空行

:set ic                              //搜索是忽略大小写
:set noic                            //搜索时区分大小写
```

### 7）、显示比较：

```C
:set nu                              //显示行号
:set nonu                            //隐藏行号
:set list                            //显示tab
:set nolist                          //隐藏tab
:noh                                 //退出搜索高亮
:source ~/.vimrc                     //更新配置文件
:hi / :highlight                     //查看当前颜色配置
:f / Ctrl + G                        //查看文件名
:pwd                                 //查看当前工作目录
:cd /home/hx/xxx                     //修改当前工作目录
:diffthis                            //比较文件，在打开的两个文件中分别执行
:diffupdate                          //比较更新
zo                                   //折叠打开
zc                                   //折叠关闭
:set fileencoding                    //查看文件编码格式
:set fileencoding=uft-8              //转换文件编码格式为utf-8
:set fileformat=unix                 //设置文件格式为unix
:set wrap                            //自动换行
:set nowrap                          //不自动换行
```

### 8）、多行注释：

```C
//-----多行注释---------//
ESC                              //退出至常规模式，光标放在行首
Ctrl + V                         //进入VISUAL BLOCK模式
nj                               //选中光标往下n行
Shift + I                        //进入插入模式
//、#                            //输入注释符
ESC                              //退出(等一会)
//-----取消多行注释-----//
ESC                              //退出至常规模式，光标放在行首
Ctrl + V                         //进入VISUAL BLOCK模式
nj                               //选中光标往下n行
x或d                             //按块删除
ESC                              //退出
```

### 9）、文件操作：

```c
:set ff                          //查看文件格式(dos/unix)
:set ff=unix                     //设置文件格式为unix
:set fileformat                  //查看文件格式(dos/unix)
:set fileformat=unix             //设置文件格式为unix
:w new_file.txt                  //vim中另存为文件

// vim已十六进制查看二进制文件：
vim -b file.dtb
:%!xxd
// 恢复成二进制显示
:%!xxd -r
```

### 10）、vim控制字符：

```c
显示样式    ASCII值    字符名称
  ^@        0x0         NUL
  ^H        0x8         退格(Backspace)
  ^I        0x9         水平制表符
  ^J        0xa         换行(\n, LN)
  ^@        0xa         换行(\n, LN)
  ^M        0xd         回车(\r, CR, Enter)

// 显示控制字符
:set invlist
// 不显示控制字符
:set nolist
// eol字符显示为$
:set listchars=eol:$
// 显示tab、eol和空格
:set listchars=tab:>-,eol:$,space:·
// 删除在文件末尾自动添加换行符，git diff能检测到
:set binary noendofline
:set bin noeol
// 在文件末尾添加换行符：
在末尾添加一行空行，保存文件，然后再删除，并再保存文件

```

### 11）、执行shell命令：

```c
// vim中执行shell命令，结果插入当前光标下一行
:r !echo " * Create: $(date '+\%a \%b \%d \%H:\%M:\%S \%Y')"
```

### 12）、tab标签：

```bash
# 新建标签
:tabnew
# 关闭当前标签
:tabc
# 关闭所有标签
:tabo
# 查看所有标签
:tabs
# 跳转至前一个标签
:tabp / gT
# 跳转至后一个标签
:tabn / gt
# 跳转是指定tab
1gt / 2gt / 3gt ......
:tabn 1 / :tabn 2 / :tabn 3 ......
```

## 2、正则表达式：

```C
\n                               //换行
\t                               //tab
\*                               //重复0次或多次
\+                               //重复1次或多次
\?                               //匹配0次或1次
\(、\)                           //小括号转义
\s                               //空白符
^                                //匹配行首
$                                //匹配行尾
:%s/\s\+$//gc                    //删除行尾空白符
:10,41s/^\(\t*\)    /\1\t/gc     //行首每4个空格替换成tab
```

## 3、vim脚本：

```c
g: varname                       //变量为全局变量
s: varname                       //变量的范围为当前的脚本文件
w: varname                       //变量的范围为当前的编辑器窗口
t: varname                       //变量的范围为当前的编辑器选项卡
b: varname                       //变量的范围为当前的编辑器缓冲区
l: varname                       //变量的范围为当前的函数
a: varname                       //变量是当前函数的一个参数
v: varname                       //变量是 Vim 的预定义变量
```

## 4、vim插件：

### 1）、Pathgyen：

```c
//离线插件管理器
//下载地址：https://github.com/tpope/vim-pathogen/
//下载到目录：~/.vim/autoload/.vim
//在~/.vimrc中加入：
execute pathogen#infect()
syntax on
filetype plugin indent on
```

### 2）、NERDTree：

```C
//显示目录树
//地址：https://github.com/scrooloose/nerdtree
cd ~/.vim/bundle                                    //进入vim插件目录
git clone git@github.com:scrooloose/nerdtree.git    //下载NERDTree
//使用：在目录树中操作节点
ctrl + w   =                     //窗口尺寸恢复均等
:NERDTreeToggle                  //切换开、关目录树
m                                //进入NERDTree Menu
    a                               //新建节点
    d                               //删除节点
    m                               //重命名节点
R                                //刷新目录树
I                                //切换显示隐藏节点
U                                //将根节点设为上级目录
C                                //将根节点设为当前节点

//书签操作
B                                //打开书签 (Shift + B)
:Bookmark <name>                 //将当前文件添加到书签，并命名为name ,name 可改成其他
:ClearBookmarks <name>           //清除指定书签
:ClearBookmarks                  //清除所有书签
:ClearAllBookmarks               //清除所有书签

:NERDTreeFind               //跳转至当前打开的文件所在路径下的目录
:NERDTreeCWD                //跳转至当前vim当前工作路径(:pwd)下的目录
```

### 3）、Taglist：

```C
//显示函数列表，需ctags支持
sudo apt install ctags                                  //安装ctags
git clone git@github.com:vim-scripts/taglist.vim.git    //下载taglist
cp taglist.txt ~/.vim/doc                               //复制taglist.txt
cp taglist.vim ~/.vim/pugin                             //复制taglist.vim
```

### 4）、astyle：

```C
//格式化代码
sudo apt install astyle          //安装astyle
astyle --version                 //查看astyle版本
:%!astyle --style=kr             //格式化当前文件
:1,40!astyle --style=kr          //格式化指定区域
```

### 5）、ctags：

```C
//函数跳转
sudo apt install ctags           //安装ctags
ctags --version                  //查看ctags版本
ctags -R *                       //递归生产tags文件
Ctrl + ]                         //(vim中)跳转至定义
Ctrl + T                         //(vim中)返回
    --languages=c                //指定语言为C语言
    --exclude=file.c             //排除文件或目录
```

### 6）、AutoComplPop：

```c
//自动补全
git clone https://gitee.com/tsingyixy/AutoComplPop.git
cd AutoComplPop
cp autoload/acp.vim ~/.vim/autoload/
cp plugin/acp.vim ~/.vim/plugin/
cp doc/* ~/.vim/doc/
```

### 7）、LeaderF：

```c
//模糊搜索
git clone https://github.com/Yggdroot/LeaderF
cp -r LeaderF ~/.vim/bundle

<leader键>：\

// 搜索当前目录下文件：
<leader键> f
// 进入/退出文件选择：
Tab

// 搜索当前Buffer：
<leader键> b

:Leaderf rg                    //使用rg搜索字符
:Leaderf rg -h                 //查看帮助
            -A num             //显示匹配行之后的num行
            -B num             //显示匹配行之前的num行
            -C num             //显示匹配行前后的num行
            -e pattern         //匹配正则表达式
//常见用法
:Leaderf rg -e 'struct mm_struct \{'                 //在当前目录下搜索
:Leaderf rg -e 'struct mm_struct \{' include         //指定目录搜索
```
### 8）、BufferExplorer：
```bash
:BufExplorer                  # 查看历史打开文件
```

### 9）、MRU：

```bash
# 查看最近打开文件：https://github.com/yegappan/mru
:MRU

# 映射到快捷键
nmap <C-a> :MRU<CR>
# 设置窗口高度
let MRU_Window_Height = 20
```

## 5、下载配色主题：

```C
//下载：[http://www.easycolor.cc/](http://www.easycolor.cc/)
cd ~/.vim/colors                                //放入指定目录(molokai.vim)
colorscheme molokai                             //在~/.vimrc中设置
```

## 6、编译vim：

```c
//源码编译安装vim提供Python支持
sudo apt-get install python-dev python3-dev libncurses5-dev xorg-dev  //安装依赖
vim --version | grep python                     //查看vim对python的支持
sudo apt --purge remove vim                     //卸载vim
git clone git@github.com:vim/vim.git            //下载vim源码
cd vim/src                                      //进入源码目录
make clean; make distclean                      //清除编译生成文件
./configure \
  --with-features=huge \                        //支持最大特性
  --enable-rubyinterp \                         //打开对ruby编写的插件的支持
  --enable-luainterp \                          //打开对lua编写的插件的支持
  --enable-perlinterp \                         //打开对perl编写的插件的支持
  --enable-multibyte \                          //打开多字节支持，可输入中文
  --enable-cscope \                             //打开对cscope的支持
  --enable-pythoninterp \                       //打开对python编写的插件的支持
  --enable-python3interp \                      //打开对python3编写的插件的支持
  --prefix=/usr/local/ \                        //安装目录
  --with-x \                                    //支持剪切板
  --with-gnome \                                //?
  --with-python-config-dir=/usr/lib/python2.7/config-x86_64-linux-gnu/ \     //指定python路径
  --with-python3-config-dir=/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/  //指定python3路径
./configure \
  --with-features=huge \
  --enable-rubyinterp \
  --enable-luainterp \
  --enable-perlinterp \
  --enable-multibyte \
  --enable-cscope \
  --enable-pythoninterp \
  --enable-python3interp \
  --prefix=/usr/local/ \
  --with-x \
  --with-gnome \
  --enable-gui=auto \
  --with-python-config-dir=/usr/lib/python2.7/config-x86_64-linux-gnu/ \
  --with-python3-config-dir=/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/
make                                            //编译
make reconfig                                   //当产生错误时
./vim --version | grep python                   //查看对python的支持
./vim --version | grep clipboard                //查看对clipboard的支持
sudo make install                               //安装
sudo mv /usr/bin/vim /usr/bin/vim-bkp           //备份原vim
vim --version | grep VIM                        //查看vim版本
vim --version | grep python                     //查看python支持
vim --version | grep clipboard                  //查看剪切板支持
```
### 1）、简单编译：
```bash
./configure --enable-pythoninterp --enable-python3interp
cd src
make -j
```

## 7、安装YouCompleteMe：

```c
git clone git@github.com:ycm-core/YouCompleteMe.git    //下载YouCompleteMe源码
cp YouCompleteMe ~/.vim/bundle/                        //复制到vim插件目录
git submodule update --init --recursive                //
```

## 8、C语言常用配色：

​```c
背景色(灰色)：RGB(39,40,34), HTML(#272822)
关键字(红色)：RGB(249,39,60), HTML(#F9273C)
宏定义(红色)：RGB(249,39,60), HTML(#F9273C)
字符串(黄色)：RGB(255,215,0), HTML(#FFD700)      //字符串、运算符
函数名(蓝色)：RGB(95,215,255), HTML(#5FD7FF)
```
