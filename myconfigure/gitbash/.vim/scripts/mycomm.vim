" 高亮函数名
syn match cFunctions "\<[a-zA-Z_][a-zA-Z_0-9]*\>[^()]*)("me=e-2
syn match cFunctions "\<[a-zA-Z_][a-zA-Z_0-9]*\>\s*("me=e-1
hi cFunctions ctermfg=81
" 高亮运算符
syn match cOperators display "[-+*%=<>|.&!^~:]"
hi cOperators ctermfg=227
