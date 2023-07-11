# echo "[ -f ~/.myshell/main.sh ] && source ~/.myshell/main.sh" >> ~/.bashrc
# echo "[ -f ~/.myshell/main.sh ] && source ~/.myshell/main.sh" >> ~/.zshrc

[ -f ~/.myshell/lib.sh   ] && source ~/.myshell/lib.sh
[ -f ~/.myshell/alias.sh ] && source ~/.myshell/alias.sh
[ -f ~/.myshell/env.sh   ] && source ~/.myshell/env.sh
[ -f ~/.myshell/path.sh  ] && source ~/.myshell/path.sh
[ -f ~/.myshell/cmd.sh   ] && source ~/.myshell/cmd.sh
[ -f ~/.cur.shell        ] && source ~/.cur.shell

if is_bash; then
    source_file ~/.myshell/bash/main.sh
elif is_zsh; then
#    DOT_MYSHELL=$(dirname "$(realpath "$0")")
    source_file ~/.myshell/zsh/main.sh
else
    echo "Cannot recognize the current shell"; exit 1
fi
