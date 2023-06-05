# echo "[ -f ~/.myshell/main.sh ] && source ~/.myshell/main.sh" >> ~/.bashrc
# echo "[ -f ~/.myshell/main.sh ] && source ~/.myshell/main.sh" >> ~/.zshrc

source ~/.myshell/alias.sh

if [ "$SHELL" == *"bash"* ]; then
    source ~/.mybash/main.sh
elif [ "$SHELL" == *"zsh"* ]; then
#    DOT_MYSHELL=$(dirname "$(realpath "$0")")
    source ~/.myzsh/main.sh
else
    echo "Cannot recognize the current shell"; exit 1
fi
