if [[ $- == *i* ]]; then
    bind '"\e[A": history-search-backward'
    bind '"\e[B": history-search-forward'
    bind '"\e[1~": beginning-of-line'
    bind '"\e[4~": end-of-line'
fi

parse_git_branch() {
    git branch 2> /dev/null | sed -n -e 's/^\* \(.*\)/ <\1>/p'
}
export PS1='\n\[\e[34m\][\u@\h]: \[\e[33m\]\w\[\e[34m\]$(parse_git_branch) \[\e[33m\]$(date "+%H:%M:%S")\n\[\e[31m\] $ \[\e[0m\]'

[ -f ~/.fzf.bash ] && source ~/.fzf.bash
