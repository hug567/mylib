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
autocmd BufNewFile,BufRead *.cc source ~/.vim/scripts/mycpp.vim
autocmd BufNewFile,BufRead *.bb,*.bbappend,*.inc,*.bbclass set syntax=sh
autocmd BufNewFile,BufRead *.sh source ~/.vim/scripts/mysh.vim

" 保存文件前设置noendofline，但此设置会复位expandtab
"autocmd BufWrite    * :set binary noendofline
"autocmd BufWritePre * :set binary noendofline
