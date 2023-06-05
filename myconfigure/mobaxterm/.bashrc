export HOME=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export TERM=xterm-256color

PS1='\[\e[34m\] [Mobaxterm] \[\e[33m\]\w\n \[\e[31m\]$ \[\e[0m\]'

alias cls='clear'
alias lsa='ls -a'
alias ll='ls -l'
alias lla='ls -la'

if [[ $- == *i* ]]; then
    bind '"\e[A": history-search-backward'
    bind '"\e[B": history-search-forward'
    bind '"\e[1~": beginning-of-line'
    bind '"\e[4~": end-of-line'
fi

[ -f ~/.my.shell ] && source ~/.my.shell
