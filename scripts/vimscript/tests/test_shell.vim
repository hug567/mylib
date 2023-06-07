" run shell cmd in vimscript
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-06-07

function! TestShellCmd()
    echo "TestShellCmd: ---------------------------------------"

    let l:pwd = system("pwd")
    echo "pwd: " .. l:pwd

    let l:kernel = system("uname -s")
    echo "kernel: " .. l:kernel
endfunction

function! Main()
    call TestShellCmd()
endfunction

call Main()
