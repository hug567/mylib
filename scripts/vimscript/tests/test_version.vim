" get vim version in vimscript
" run: vim -c 'source test_xxx.vim'
" 2023-05-23

function! TestGetVersion()
    echo "TestGetVersion: -------------------------------------"
    let l:var = version
    echo "current vim version: " .. l:var
endfunction

func! Main()
    call TestGetVersion()
endfunc

call Main()
