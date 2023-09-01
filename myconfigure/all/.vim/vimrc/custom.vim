"------------------------------------------------------------------------------"
" 在命令行输出寄存器'0'的内容
func! MyPrintReg0Contents()
    let lines = getreg("0")
    echo lines
endfunc
map <F8> :call MyPrintReg0Contents()<CR>

"------------------------------------------------------------------------------"
" 保存寄存器"中的内容到临时文件中
func! SaveToTmpFile()
    let lines = getreg("\"")
    let len = strlen(lines)
    let i = 0
    let list = []
    let line_num = 0
    let substart = 0
    let endidx = len - 1
    let l:tmp_dir = "/tmp/vim"
    let l:tmp_file = "/tmp/vim/paste.txt"
    while i < len
       if lines[i] == "\n" || i == endidx
            let sublen = i - substart
            if i == endidx && lines[i] != "\n"
                let sublen += 1
            endif
            let substr = strpart(lines, substart, sublen)
            call add(list, substr)
            let substart = i + 1
            let line_num += 1
        endif
        let i += 1
    endwhile
    if ! isdirectory(l:tmp_dir)
        call mkdir(l:tmp_dir)
    endif
    call writefile(list, l:tmp_file)
    if line_num > 0
        echo line_num . " lines yanked, and save to tmp file"
    endif
endfunc
"delcommand SaveToTmpFile
command SaveToTmpFile call SaveToTmpFile()
" y命令复制时自动写入临时文件
if IsGreaterVim800()
    autocmd TextYankPost * :call SaveToTmpFile()
endif

" 读取临时文件到寄存器0中
func! LoadFromTmpFile()
    let l:tmp_dir = "/tmp/vim"
    let l:tmp_file = "/tmp/vim/paste.txt"
    if ! isdirectory(l:tmp_dir) || ! filereadable(l:tmp_file)
        return
    endif
    let list = readfile(l:tmp_file)
    call setreg("\"", list)
    call setreg("0", list)
    call setreg("1", list)
    silent execute "put"
    echo "read tmp file to reg[0]"
endfunc
"delcommand LoadFromTmpFile
command LoadFromTmpFile call LoadFromTmpFile()
" Ctrl-P实现读取临时文件中内容并粘贴
map <C-p> :call LoadFromTmpFile()<CR>
"------------------------------------------------------------------------------"

func! CreateTime()
    let l:date = system("date '+%Y-%m-%d %H:%M:%S'")
    let l:str = " * Create: " .. l:date
    " delete tail char
    let l:len = len(l:str)
    let l:newstr = strpart(l:str, 0, len - 1)
    " insert on the line under the cursor
    call append(line('.'), l:newstr)
    " move the cursor to the next line
    normal! j
endfunction
command Createtime call CreateTime()
"------------------------------------------------------------------------------"
