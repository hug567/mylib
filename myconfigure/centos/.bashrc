# .bashrc

# User specific aliases and functions

alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

parse_git_branch() {
    git branch 2> /dev/null | sed -n -e 's/^\* \(.*\)/ <\1>/p'
}
export PS1='\n\[\e[34m\][\u@\h]: \[\e[33m\]\w\[\e[34m\]$(parse_git_branch) \[\e[33m\]$(date "+%H:%M:%S")\n\[\e[31m\] $ \[\e[0m\]'
