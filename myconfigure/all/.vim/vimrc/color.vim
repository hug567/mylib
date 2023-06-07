" 设置配色主题
colorscheme molokai

"------------------------------------------------------------------------------"
" 主窗口背景色
hi Normal ctermbg=NONE
" 行号列背景色
hi LineNr ctermbg=NONE
" VISUAL模式选中背景色
hi Visual ctermfg=235 ctermbg=228
" VISUAL LINE模式选中背景色
hi VisualNOS term=NONE cterm=NONE ctermfg=235 ctermbg=228
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
" 高亮多个列
"let &colorcolumn="80,120"
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
" Error颜色：白
hi Error  ctermfg=252 ctermbg=NONE
"------------------------------------------------------------------------------"
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
"------------------------------------------------------------------------------"
