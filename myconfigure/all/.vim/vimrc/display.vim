" 显示行号
set number
" 搜索过程中高亮
set hlsearch
" 逐个字符高亮
set incsearch
" 自动缩进
set autoindent
" 显示tab
set list
" 设置tab显示格式
set listchars=tab:>-,trail:-
" 开启鼠标功能
"set mouse=a
"set selection=exclusive
"set selectmode=mouse,key
" 搜索不区分大小写
set ignorecase
" 设置光标样式
let &t_SI.="\e[2 q" "INSERT模式，2:方块
if IsGreaterVim800()
let &t_SR.="\e[2 q" "REPLACE模式, 2:方块
endif
let &t_EI.="\e[2 q" "NORMAL模式, 2:方块
" 使能系统剪切板+ (vim需支持+clipboard)
"set clipboard^=unnamed,unnamedplus

if IsMobaxterm()
    set nofoldenable
endif
