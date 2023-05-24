" learning vimscript logic
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" 2023-05-24

function! TestLogic()
    echo "TestLogic: ------------------------------------------"
    echo getcwd()
    echo expand('%:h')
endfunction

function! Main()
    call TestLogic()
endfunction

call Main()
