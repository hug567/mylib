# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific environment
if ! [[ "$PATH" =~ "$HOME/.local/bin:$HOME/bin:" ]]
then
    PATH="$HOME/.local/bin:$HOME/bin:$PATH"
fi
export PATH

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
if [ -d ~/.bashrc.d ]; then
	for rc in ~/.bashrc.d/*; do
		if [ -f "$rc" ]; then
			. "$rc"
		fi
	done
fi

unset rc

################################# 自定义配置 #################################
alias lsa='ls -a'
alias cls='clear'
alias tmux='tmux -2'
export TERM=xterm-256color

parse_git_branch() {
    git branch 2> /dev/null | sed -n -e 's/^\* \(.*\)/ <\1>/p'
}
export PS1='\n\[\e[34m\][\u@\h]: \[\e[33m\]\w\[\e[34m\]$(parse_git_branch) \[\e[33m\]$(date "+%H:%M:%S")\n\[\e[31m\] $ \[\e[0m\]'
################################# 自定义配置 #################################
