" vim单文件基本配置
" 主窗口背景色
hi Normal ctermbg=NONE
" 行号列背景色
hi LineNr ctermbg=NONE ctermfg=15
" VISUAL模式选中背景色
hi Visual ctermfg=235 ctermbg=228
" VISUAL LINE模式选中背景色
hi VisualNOS term=NONE cterm=NONE ctermfg=235 ctermbg=228
" 光标所在行背景色
set cursorline
hi CursorLine cterm=NONE ctermbg=237
hi CursorLineNr cterm=NONE
" 高亮匹配括号
hi MatchParen ctermfg=208 ctermbg=240
" 搜索高亮
hi Search ctermbg=220
" 列宽提示宽度及背景色
let &colorcolumn="80,120"
hi ColorColumn ctermbg=237
" 分屏线颜色
hi VertSplit ctermfg=245 ctermbg=NONE
" 取消搜索高亮快捷键
map <F12> :noh<CR>
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
" 搜索不区分大小写
set ignorecase
