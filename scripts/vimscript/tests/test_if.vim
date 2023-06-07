" learning vimscript if
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-05-23

function! TestIf()
    echo "TestIf: ---------------------------------------------"
    let l:num = 10

    " if
    if l:num == 10
        echo "l:num == " .. l:num
    endif

    " if - else
    if l:num > 10
        echo "l:num > 10"
    else
        echo "l:num <= 10"
    endif

    " if - elseif - else
    if l:num > 10
        echo "l:num > 10"
    elseif l:num == 10
        echo "l:num == 10"
    else
        echo "l:num < 10"
    endif
endfunction

function! __ReturnTrue()
    return 1
endfunction

function! __ReturnFalse()
    return 0
endfunction

function! TestFunctionReturn()
    echo "TestFunctionReturn: ---------------------------------"

    if __ReturnTrue()
        echo "function return true"
    endif

    if ! __ReturnFalse()
        echo "function return false"
    endif
endfunction

function! Main()
    call TestIf()
    call TestFunctionReturn()
endfunction

call Main()
