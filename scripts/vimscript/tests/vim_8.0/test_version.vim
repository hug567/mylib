" 在vim中运行：
"   :source .../test_version.vim
" 或进入文件目录后再运行：
"   :cd vimscript/tests/vim_8.0
"   :source test_version.vim
" 2025-03-06

function! TestGetVersion()
    echo "TestGetVersion: -------------------------------------"
    " 值为800，l:var为函数中的局部变量
    let l:var = version
    " vim 8.0连接字符串为单个点符号
    echo "current vim version: " . l:var
endfunction

function! Main()
    call TestGetVersion()
endfunction

call Main()
