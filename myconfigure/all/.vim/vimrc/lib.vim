function! IsLinux()
    let l:kernel = system("uname -s")
    if match(l:kernel, "Linux") != -1
        return 1
    else
        return 0
    endif
endfunction

function! CmdExist(cmd)
    let l:cmdstr = printf("%s%s", "type ", a:cmd)
    let l:ret = system(l:cmdstr)
    if match(l:ret, "not found") != -1
        return 0
    else
        return 1
    endif
endfunction

function! __IsVimVersion(ver)
    let l:v = version
    if l:v == a:ver
        return 1
    else
        return 0
    endif
endfunction

function! IsVim703()
    return __IsVimVersion(703)
endfunction

function! IsVim800()
    return __IsVimVersion(800)
endfunction

function! IsVim801()
    return __IsVimVersion(801)
endfunction

function! IsVim802()
    return __IsVimVersion(802)
endfunction

function! IsGreaterVim800()
    let l:v = version
    if l:v >= 800
        return 1
    else
        return 0
    endif
endfunction

"------------------------------------------------------------------------------"

function! TestShellCmd()
    echo "TestShellCmd: ---------------------------------------"
    if IsLinux()
        echo "current is linux"
    endif

    if CmdExist("vim") && ! CmdExist("yyy")
        echo "cmd vim exist, and cmd yyy does not exist"
    endif

    if ! CmdExist("xxx")
        echo "cmd xxx does not exist"
    endif
endfunction

function! Main()
    call TestShellCmd()
endfunction

"call Main()
