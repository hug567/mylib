" learning insert text to vim
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-09-01

function! TestInsertText()
    echo "TestInsertText: -------------------------------------"
    let l:date = system("date '+%Y-%m-%m %H:%M:%S'")
    let l:str = " * Create: " .. l:date
    " delete tail char
    let l:len = len(l:str)
    let l:newstr = strpart(l:str, 0, len - 1)
    " insert on the line under the cursor
    call append(line('.'), l:newstr)
    " move the cursor to the next line
    normal! j
endfunction

function! Main()
    call TestInsertText()
endfunction

call Main()
