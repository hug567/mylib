" jump to tab: \+1, \+2, \+3 ...
noremap <silent><leader>1 :tabn 1<CR>
noremap <silent><leader>2 :tabn 2<CR>
noremap <silent><leader>3 :tabn 3<CR>
noremap <silent><leader>4 :tabn 4<CR>
noremap <silent><leader>5 :tabn 5<CR>
noremap <silent><leader>6 :tabn 6<CR>
noremap <silent><leader>7 :tabn 7<CR>
noremap <silent><leader>8 :tabn 8<CR>
noremap <silent><leader>9 :tabn 9<CR>
noremap <silent><leader>0 :tabs  <CR>
noremap <silent><leader>n :tabnew<CR>
noremap <silent><leader>c :tabc<CR>

" custom tab color
hi TabLine     term=standout cterm=standout ctermfg=242 ctermbg=15
hi TabLineSel  term=bold cterm=bold gui=bold ctermfg=220 ctermbg=242
hi TabLineFill term=standout cterm=standout ctermfg=242 ctermbg=15
