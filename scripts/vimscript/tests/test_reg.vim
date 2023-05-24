" learning vimscript register
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" 2023-05-24

function! TestRegister()
    echo "TestRegister: ---------------------------------------"
    echo @a
endfunction

function! Main()
    call TestRegister()
endfunction

call Main()
