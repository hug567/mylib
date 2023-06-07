" learning vimscript logic
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-05-24

" and or not
function! TestLogic()
    echo "TestLogic: ------------------------------------------"
    if 1 == 1 && 2 < 3
        echo "1 == 1 && 2 < 3"
    endif

    if 1 > 2 || 2 < 3
        echo "1 > 2 || 2 < 3"
    endif

    if ! 0
        echo "!0"
    endif
endfunction

function! Main()
    call TestLogic()
endfunction

call Main()
