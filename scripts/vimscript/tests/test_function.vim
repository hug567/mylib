" learning vimscript function
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-05-22

" function without parameters and return value
" must start with uppercase letters
function! TestPrint()
    echo "TestPrint: ------------------------------------------"
    echo "hello vimscript"
endfunction

function! TestPrintInfo(name, age)
    echo "TestPrintInfo: --------------------------------------"
    echo "name: " .. a:name .. ", age: " .. a:age
endfunction

" shorthand keywords: func / endfunc
func! TestReturn(num01, num02)
    echo "TestReturn: -----------------------------------------"
    return a:num01 + a:num02
endfunc

function! Main()
    " function call
    call TestPrint()
    " function call with parameters
    call TestPrintInfo("Bob", 18)
    " function call and get return value
    echo "1 + 2 = " .. TestReturn(1, 2)
endfunction

call Main()
