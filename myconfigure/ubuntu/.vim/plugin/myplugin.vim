function! s:PrintCopyContents()
    let lines = getreg("0")
    echo lines
endfunction

command! -nargs=0 -bar PrintCopyContents call s:PrintCopyContents()
