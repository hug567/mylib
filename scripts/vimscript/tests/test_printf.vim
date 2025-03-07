" 在vim中运行：
"   :source .../test_printf.vim
" 或进入文件目录后再运行：
"   :cd vimscript/tests
"   :source test_printf.vim
" 2025-03-06

" printf格式化输出：已验证vim 8.0/8.2/9.1
function! TestPrintf()
    echo "TestPrintfStr: ------------------------------------------------------"
    " printf格式化输出整数
    let l:var = version
    let l:str = printf("current vim version: %d", l:var)
    echo l:str

    " printf格式化输出字符串
    let l:name = 'Tom'
    let l:str = printf("my name is: %s", l:name)
    echo l:str
endfunction

function! Main()
    call TestPrintf()
endfunction

call Main()
