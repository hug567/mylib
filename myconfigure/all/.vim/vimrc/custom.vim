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
    call writefile(list, '/tmp/vim_tmp.txt')
    if line_num > 0
        echo line_num . " lines yanked, and save to tmp file /tmp/vim_tmp.txt"
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
    if ! filereadable("/tmp/vim_tmp.txt")
        echo "/tmp/vim_tmp.txt does not exist"
        return
    endif
    let l:list = readfile("/tmp/vim_tmp.txt")
    let l:str = join(l:list, nr2char(10))
    call setreg("\"", l:str)
    call setreg("0", l:str)
    call setreg("1", l:str)
    silent execute "put"
    echo "read tmp file /tmp/vim_tmp.txt to reg[0]"
endfunc
"delcommand LoadFromTmpFile
command LoadFromTmpFile call LoadFromTmpFile()
" Ctrl-P实现读取临时文件中内容并粘贴
map <C-p> :call LoadFromTmpFile()<CR>
"------------------------------------------------------------------------------"
