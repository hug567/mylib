source ~/.vim/vimrc/lib.vim
source ~/.vim/vimrc/plugin.vim
source ~/.vim/vimrc/color.vim
source ~/.vim/vimrc/display.vim
source ~/.vim/vimrc/nerdtree.vim
source ~/.vim/vimrc/taglist.vim
source ~/.vim/vimrc/leaderf.vim
source ~/.vim/vimrc/autocmd.vim
source ~/.vim/vimrc/custom.vim
source ~/.vim/vimrc/cscope.vim
source ~/.vim/vimrc/mru.vim
source ~/.vim/vimrc/tab.vim

let ver = version
if ver == 800
    source ~/.vim/vimrc/vimrc-8.0
elseif ver == 801
    source ~/.vim/vimrc/vimrc-8.1
endif
