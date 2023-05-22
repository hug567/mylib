" learning vimscript function
" run: vim -c "source test_function.vim"
" 2023-05-22

" function without parameters and return value
" must start with uppercase letters
function! TestPrint()
    echo "hello vimscript"
endfunction

function! TestPrintInfo(name, age)
    echo "name: " .. a:name .. ", age: " .. a:age
endfunction

function! TestReturn(num01, num02)
    return a:num01 + a:num02
endfunction

func! Main()
    " function call
    call TestPrint()
    " function call with parameters
    call TestPrintInfo("Bob", 18)
    " function call with return value
    echo "1 + 2 = " .. TestReturn(1, 2)
endfunc

call Main()
