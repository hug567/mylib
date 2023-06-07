" learning vimscript file operation
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-05-24

function! TestFileExist()
    echo "TestFileExist: --------------------------------------"

    let l:file = "/tmp/vim_tmp.txt"
    if filereadable(l:file)
        echo "file " .. l:file .. " exist"
    endif

    if ! filereadable(expand("$HOME/test.txt"))
        echo "file " .. expand("$HOME/test.txt") .. " does not exist"
    endif
endfunction

function! Main()
    call TestFileExist()
endfunction

call Main()
