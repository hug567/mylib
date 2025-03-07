" get vim version in vimscript
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-05-23

function! TestGetVersion()
    echo "TestGetVersion: -------------------------------------"
    let var = version
    echo "current vim version: " . var
endfunction

function! Main()
    call TestGetVersion()
endfunction

call Main()
