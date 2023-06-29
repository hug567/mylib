" learning vimscript dir operation
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-06-29

function! TestDirExist()
    echo "TestDirExist: ---------------------------------------"

    let l:dir = "/tmp/vim"
    if isdirectory(l:dir)
        echo "dir " .. l:dir " exist"
    else
        echo "dir " .. l:dir " does not exist"
    endif
endfunction

function! TestCreateDelDir()
    echo "TestCreateDelDir: -----------------------------------"

    let l:dir = "/tmp/testdir"
    if isdirectory(l:dir)
        echo "dir " .. l:dir " exist"
    else
        echo "dir " .. l:dir " does not exist, will create it"
        call mkdir(l:dir)
    endif
    call delete(l:dir, 'd')
endfunction

function! Main()
    call TestDirExist()
    call TestCreateDelDir()
endfunction

call Main()
