" learning vimscript compare number
" run: vim -c 'source test_xxx.vim'
" 2023-05-23

function! TestCmpNum()
    echo "TestCmpNum: -----------------------------------------"
    let num1 = 5
    let num2 = 3
    if num1 > num2
        echo num1 .. " > " .. num2
    endif

    let num1 = 5
    let num2 = 6
    if num1 < num2
        echo num1 .. " < " .. num2
    endif

    let num1 = 6
    let num2 = 6
    if num1 == num2
        echo num1 .. " == " .. num2
    endif

    let num1 = 8
    let num2 = 6
    if num1 >= num2
        echo num1 .. " >= " .. num2
    endif

    let num1 = 9
    let num2 = 9
    if num1 <= num2
        echo num1 .. " <= " .. num2
    endif
endfunction

func! Main()
    call TestCmpNum()
endfunc

call Main()
