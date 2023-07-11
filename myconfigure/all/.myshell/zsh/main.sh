export ZSH=$HOME/.oh-my-zsh
ZSH_THEME="ys"

plugins=(
    git
    zsh-autosuggestions
)

# 记录历史命令
export HISTFILE="$HOME/.zsh_history"
export HISTSIZE=10000000
export SAVEHIST=$HISTSIZE

# 修复Home、End不可用
bindkey '\e[1~' beginning-of-line
bindkey '\e[4~' end-of-line
bindkey "\E[H" beginning-of-line
bindkey "\E[F" end-of-line
bindkey "\E[3~" delete-char

# 打开颜色模式
autoload -U colors && colors

source_file $ZSH/oh-my-zsh.sh
source_file ~/.fzf.zsh
