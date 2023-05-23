" learning vimscript compare number
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" 2023-05-23

function! TestCmpNum()
    echo "TestCmpNum: -----------------------------------------"
    let l:num1 = 5
    let l:num2 = 3
    if l:num1 > l:num2
        echo l:num1 .. " > " .. l:num2
    endif

    let l:num1 = 5
    let l:num2 = 6
    if l:num1 < l:num2
        echo l:num1 .. " < " .. l:num2
    endif

    let l:num1 = 6
    let l:num2 = 6
    if l:num1 == l:num2
        echo l:num1 .. " == " .. l:num2
    endif

    let l:num1 = 8
    let l:num2 = 6
    if l:num1 >= l:num2
        echo l:num1 .. " >= " .. l:num2
    endif

    let l:num1 = 9
    let l:num2 = 9
    if l:num1 <= l:num2
        echo l:num1 .. " <= " .. l:num2
    endif
endfunction

function! TestCmpString()
    echo "TestCmpString: --------------------------------------"
endfunction

function! Main()
    call TestCmpNum()
    call TestCmpString()
endfunction

call Main()
