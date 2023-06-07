" 只显示当前文件tag
let Tlist_Show_One_File=1
" Taglist为最后一个窗口时退出vim
let Tlist_Exit_OnlyWindow=1
 "Taglist与ctags关联
let Tlist_Ctags_Cmd="/usr/bin/ctags"
" Taglist窗口显示在右侧
let Tlist_Use_Right_Window =1
" Taglist窗口宽度
let Tlist_WinWidth = 40
" Taglist折叠列颜色
hi FoldColumn ctermbg=NONE
" Taglist开启、关闭快捷键
map <F6> :TlistOpen<CR>
map <F7> :TlistClose<CR>

