"------------------------------------------------------------------------------"
" 离线插件管理器: pathogen
execute pathogen#infect()
syntax on
filetype plugin indent on

"------------------------------------------------------------------------------"
" 显示行号
set number
" 搜索过程中高亮
set hlsearch
" 逐个字符高亮
set incsearch
" 自动缩进
set autoindent
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
" 搜索不区分大小写
set ignorecase
" 设置光标样式
let &t_SI.="\e[2 q" "INSERT模式，2:方块
let &t_SR.="\e[2 q" "REPLACE模式, 2:方块
let &t_EI.="\e[2 q" "NORMAL模式, 2:方块
" 使能系统剪切板+ (vim需支持+clipboard)
"set clipboard^=unnamed,unnamedplus

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
" 打开NERDTree快捷键
map <F9> :NERDTreeToggle<CR>
set backspace=indent,eol,start
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
" 忽略指定文件
let NERDTreeIgnore=['\.o$', '\.elf', '\.swp$', '\.out$']

"------------------------------------------------------------------------------"
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
" Taglist折叠列颜色
hi FoldColumn ctermbg=NONE
" Taglist开启、关闭快捷键
map <F6> :TlistOpen<CR>
map <F7> :TlistClose<CR>

"------------------------------------------------------------------------------"
"" 新建文件自动插入文件头
"autocmd BufNewFile *.cpp,*.[ch],*.sh,*.py,*.java exec ":call SetTitle()"
"" 定义函数SetTitle，自动插入文件头
"func SetTitle()
"    if &filetype == 'c'
"        call setline(1,"/*")
"        call append(line(".")," * Description: xxx")
"        call append(line(".")+1, " * Author: huangxing567@163.com")
"        call append(line(".")+2, " * Create: ".strftime("%Y-%m-%d %H:%M:%S"))
"        call append(line(".")+3, " */")
"        call append(line(".")+4, "")
"    endif
"endfunc
"" 新建文件后，自动定位到末尾
"autocmd BufNewFile * normal G

"------------------------------------------------------------------------------"
" 根据文件后缀加载配置文件
autocmd BufNewFile,BufRead *.c source ~/.vim/scripts/myc.vim
autocmd BufNewFile,BufRead *.h source ~/.vim/scripts/myc.vim
autocmd BufNewFile,BufRead *.py source ~/.vim/scripts/mypython.vim
autocmd BufNewFile,BufRead *.html source ~/.vim/scripts/myhtml.vim
autocmd BufNewFile,BufRead *.cpp source ~/.vim/scripts/mycpp.vim
autocmd BufNewFile,BufRead *.sh source ~/.vim/scripts/mysh.vim
" 保存文件前设置noendofline
autocmd BufWrite    * :set binary noendofline
autocmd BufWritePre * :set binary noendofline
"------------------------------------------------------------------------------"
map <F10> :LeaderfFile<CR>

"------------------------------------------------------------------------------"
" 自动补全成对括号
"inoremap ( ()<LEFT>
"inoremap [ []<LEFT>
"inoremap { {}<LEFT>
"inoremap " ""<LEFT>
"inoremap ' ''<LEFT>
"inoremap < <><LEFT>

"------------------------------------------------------------------------------"
" 在命令行输出寄存器'0'的内容
func! MyPrintReg0Contents()
    let lines = getreg("0")
    echo lines
endfunc
map <F8> :call MyPrintReg0Contents()<CR>

"------------------------------------------------------------------------------"
" 保存寄存器"中的内容到临时文件中
func! SaveToTmpFile()
    let lines = getreg("\"")
    let len = strlen(lines)
    let i = 0
    let list = []
    let line_num = 0
    let substart = 0
    let endidx = len - 1
    while i < len
       if lines[i] == "\n" || i == endidx
            let sublen = i - substart
            if i == endidx && lines[i] != "\n"
                let sublen += 1
            endif
            let substr = strpart(lines, substart, sublen)
            call add(list, substr)
            let substart = i + 1
            let line_num += 1
        endif
        let i += 1
    endwhile
    call writefile(list, '/tmp/vim_tmp.txt')
    if line_num > 0
        echo line_num . " lines yanked, and save to tmp file /tmp/vim_tmp.txt"
    endif
endfunc
"delcommand SaveToTmpFile
command SaveToTmpFile call SaveToTmpFile()
" y命令复制时自动写入临时文件
autocmd TextYankPost * :call SaveToTmpFile()

" 读取临时文件到寄存器0中
func! LoadFromTmpFile()
    let list = readfile("/tmp/vim_tmp.txt")
    call setreg("\"", list)
    call setreg("0", list)
    call setreg("1", list)
    silent execute "put"
    echo "read tmp file /tmp/vim_tmp.txt to reg[0]"
endfunc
"delcommand LoadFromTmpFile
command LoadFromTmpFile call LoadFromTmpFile()
" Ctrl-P实现读取临时文件中内容并粘贴
map <C-p> :call LoadFromTmpFile()<CR>

"------------------------------------------------------------------------------"
" 加载cscope文件
cs add cscope.out
" Ctrl + ] 跳转至定义处
nmap <C-]> :cs find g <C-R>=expand("<cword>")<CR><CR>

"------------------------------------------------------------------------------"
" MRU插件：Most Recently Used，列出最近打开的文件
let MRU_Window_Height = 20
nmap <C-a> :MRU<CR>
"------------------------------------------------------------------------------"