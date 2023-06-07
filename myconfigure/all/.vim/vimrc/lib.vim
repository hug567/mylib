function! IsLinux()
    let l:kernel = system("uname -s")
    if match(l:kernel, "Linux") != -1
        return 1
    else
        return 0
    endif
endfunction

"function! ExistCmd(cmd)
"    let l:ret = system("type")
"    if match(l:kernel, "Linux") != -1
"        return 1
"    else
"        return 0
"    endif
"endfunction

"------------------------------------------------------------------------------"

function! TestShellCmd()
    echo "TestShellCmd: ---------------------------------------"
    if IsLinux()
        echo "current is linux"
    endif
endfunction

function! Main()
    call TestShellCmd()
endfunction

call Main()
