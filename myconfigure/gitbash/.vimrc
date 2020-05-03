"-----------------------------------------------"
" 离线插件管理器: pathogen
execute pathogen#infect()
syntax on
filetype plugin indent on
"-----------------------------------------------"
" 显示行号
set number
" 搜索过程中高亮
set hlsearch
" 逐个字符高亮
set incsearch
" 设置配色主题
colorscheme molokai
" 显示tab
set list
" 设置tab显示格式
set listchars=tab:>-,trail:-
" 开启鼠标功能
"set mouse=a
"set selection=exclusive
"set selectmode=mouse,key
" 设置tab键默认为4个空格
set ts=4
set sts=4
" 自动缩进空格数
set sw=4
set expandtab
" 自动缩进
set autoindent
"-----------------------------------------------"
" 主窗口背景色
hi Normal ctermbg=NONE
" 行号列背景色
hi LineNr ctermbg=NONE
" VISUAL模式选中背景色
hi Visual ctermfg=226 ctermbg=243
" 光标背景色
"hi Cursor ctermbg=208
" 光标所在行背景色
set cursorline
hi CursorLine ctermbg=237
" 高亮匹配括号
hi MatchParen ctermfg=208 ctermbg=240
" 搜索高亮
hi Search ctermbg=220
" 列宽提示宽度及背景色
let &colorcolumn="80"
hi ColorColumn ctermbg=237
" 高亮行尾空白符
hi ExtraWhitespace ctermbg=red
autocmd ColorScheme * hi ExtraWhitespace ctermbg=red
match ExtraWhitespace /\s\+$\| \+\ze\t/
" 分屏线颜色
hi VertSplit ctermfg=245 ctermbg=NONE
" 取消搜索高亮快捷键
map <F12> :noh<CR>
" 加载~/.vimrc快捷键
map <S-F12> :source ~/.vimrc<CR>
" 设置光标样式 (1-6)
let &t_SI.="\e[2 q" "插入模式：方块
let &t_SR.="\e[2 q" "替换模式：方块
let &t_EI.="\e[2 q" "常规模式：方块
"-----------------------------------------------"
" 注释
hi Comment ctermfg=245
" 字符
hi Character ctermfg=220
" 字符串
hi String ctermfg=220
" 整型常量
hi Number ctermfg=141
" 浮点型常量
hi Float ctermfg=141
" if else switch等
hi Conditional cterm=NONE ctermfg=198
" for do while等
hi Repeat cterm=NONE ctermfg=198
" case default等
hi Label ctermfg=198
" sizeof等
hi Operator ctermfg=198
" char short int long float double signed unsigned bool void等
hi Type ctermfg=198
" auto static register volatile extern const等
hi StorageClass ctermfg=198
" struct union enum typedef等
hi Structure ctermfg=198
" #define等
hi Macro ctermfg=198
" #if #else #endif #ifdef #ifndef等
hi PreCondit cterm=NONE ctermfg=198
" #include等
hi PreProc ctermfg=198
" \n \t \r \d \u \x \f等转义字符
hi SpecialChar cterm=NONE ctermfg=198
" break continue goto return asm等
hi Statement cterm=NONE ctermfg=198
" true false等
hi Constant cterm=NONE ctermfg=141
" sizeof等
hi Operator ctermfg=198
"-----------------------------------------------"
" 打开NERDTree快捷键
map <F9> :NERDTreeToggle<CR>
set backspace=indent,eol,start
" 排除文件
let NERDTreeIgnore = ['\.exe$']
" 目录颜色
hi NERDTreeDir ctermfg=81
" 目录斜线颜色
hi NERDTreeDirSlash ctermfg=255
" 已展开目录标点颜色
hi NERDTreeClosable ctermfg=191
" 未展开目录标点颜色
hi NERDTreeOpenable ctermfg=81
" 上级目录颜色
hi NERDTreeUp ctermfg=226
" 文件节点颜色
hi NERDTreeFile ctermfg=253
" 可执行文件颜色
hi NERDTreeExecFile ctermfg=119
" 根节点颜色
hi NERDTreeCWD ctermfg=198
"-----------------------------------------------"
" 只显示当前文件tag
let Tlist_Show_One_File=1
" Taglist为最后一个窗口时退出vim
let Tlist_Exit_OnlyWindow=1
 "Taglist与ctags关联
let Tlist_Ctags_Cmd="/usr/bin/ctags"
" Taglist窗口显示在右侧
let Tlist_Use_Right_Window =1
" Taglist窗口宽度
let Tlist_WinWidth = 40
" Taglist开启、关闭快捷键
map <F6> :TlistOpen<CR>
map <F7> :TlistClose<CR>
"-----------------------------------------------"
" 根据扩展名自动加载配置文件
autocmd BufNewFile,BufRead *.c source ~/.vim/scripts/myc.vim
autocmd BufNewFile,BufRead *.h source ~/.vim/scripts/myc.vim
autocmd BufNewFile,BufRead *.cpp source ~/.vim/scripts/mycpp.vim
"-----------------------------------------------"
