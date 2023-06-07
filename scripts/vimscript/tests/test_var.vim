" learning vimscript variable
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-05-23

" var scope: global
let g:name = "Bob"

" var scope: current vimscript
let s:occupation = "programmer"

function! TestVar()
    echo "TestVar: --------------------------------------------"
    let num = 10
    echo "num: " .. num

    let str = "hello vimscript"
    echo "str: " .. str
endfunction

function! TestVarScope()
    echo "TestVarScope: ---------------------------------------"

    echo "global var name: " .. g:name
    echo "current vimscript var occupation: " .. s:occupation

    " var scope: current function
    let l:age = 18
    echo "local age: " .. l:age
endfunction

function! Main()
    call TestVar()
    call TestVarScope()
endfunction

call Main()
