" 高亮函数名
syn match cFunctions "\<[a-zA-Z_][a-zA-Z_0-9]*\>[^()]*)("me=e-2
syn match cFunctions "\<[a-zA-Z_][a-zA-Z_0-9]*\>\s*("me=e-1
hi cFunctions ctermfg=81
" 高亮运算符
syn match cOperators display "[-+*%=<>|.&!^~:]"
hi cOperators ctermfg=227
" 高亮自定义关键字
syn keyword cKeywords u8 u16 u32 u64 s8 s16 s32 s64
syn keyword cKeywords U8 U16 U32 U64 S8 S16 S32 S64 typeof string
hi cKeywords ctermfg=198

" 设置自动缩进为2个空格
set autoindent expandtab tabstop=2 shiftwidth=2 softtabstop=2
