" 加载cscope文件
cs add cscope.out
" Ctrl + ] 跳转至定义处
nmap <C-]> :cs find g <C-R>=expand("<cword>")<CR><CR>
