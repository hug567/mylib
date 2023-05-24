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
"let NERDTreeIgnore=['\.o$', '\.elf', '\.swp$', '\.out$']
