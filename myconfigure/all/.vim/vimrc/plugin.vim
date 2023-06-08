" pathogen: automatically load plug-ins from ~/.vim/bundle
"execute pathogen#infect()
"syntax on
"filetype plugin indent on

" vim-plug: https://github.com/junegunn/vim-plug
" cmds:
"   PlugInstall [name ...] [#threads]   Install plugins
"   PlugUpdate [name ...] [#threads]    Install or update plugins
"   PlugClean[!]                        Remove unlisted plugins (bang version will clean without prompt)
"   PlugUpgrade                         Upgrade vim-plug itself
"   PlugStatus                          Check the status of plugins
"   PlugDiff                            Examine changes from the previous update and the pending changes
"   PlugSnapshot[!] [output path]       Generate script for restoring the current snapshot of the plugins
call plug#begin()
    " https://github.com/preservim/nerdtree
    Plug 'preservim/nerdtree', { 'on': 'NERDTreeToggle' }

    if IsLinux() && CmdExist("python3")
        " https://github.com/Yggdroot/LeaderF
        Plug 'Yggdroot/LeaderF', { 'do': ':LeaderfInstallCExtension' }
    endif

    " https://github.com/yegappan/mru
    Plug 'yegappan/mru'

    " https://github.com/tpope/vim-fugitive
    " cmds:
    "   :Git blame
    "   :Git branch
    "   :Git diff
    Plug 'tpope/vim-fugitive'
call plug#end()
