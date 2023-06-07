" learning vimscript string
" vim version: 8.1
" run: vim -c 'source test_xxx.vim'
" run: :cd .../vimscript/tests
"      :source test_xxx.vim
" 2023-06-07

function! TestStringCmp()
    echo "TestStringCmp: --------------------------------------"

    let l:str1 = "hello"
    let l:str2 = "hello"
    if l:str1 == l:str2
        echo l:str1 .. " == " .. l:str2
    endif

    let l:str2 = "world"
    if l:str1 != l:str2
        echo l:str1 .. " != " .. l:str2
    endif

    let l:str2 = ""
    if empty(l:str2)
        echo "str2 is empty"
    endif

    if empty(l:str1) != -1
        echo "str1 is not empty: " .. l:str1
    endif
endfunction

function! TestSubString()
    echo "TestSubString: --------------------------------------"

    let l:str = "hello world"
    let l:sub = "hello"
    if match(l:str, l:sub) != -1
        echo "[" .. l:str .. "] contain [" .. l:sub .. "]"
    endif

    let l:sub = "xxx"
    if match(l:str, l:sub) == -1
        echo "[" .. l:str .. "] does not contain [" .. l:sub .. "]"
    endif
endfunction

function! TestStrCombine()
    echo "TestStrCombine: -------------------------------------"

    let l:str1 = "hello"
    let l:str2 = "world"

    " method 1
    let l:comb = l:str1 .. l:str2
    echo "l:comb: " .. l:comb

    " method 2
    let l:comb .= " in vimscript"
    echo "l:comb: " .. l:comb

    " method 3
    let l:comb = printf("%s%s", "hello", " vimscript")
    echo "l:comb: " .. l:comb
endfunction

function! Main()
    call TestStringCmp()
    call TestSubString()
    call TestStrCombine()
endfunction

call Main()
