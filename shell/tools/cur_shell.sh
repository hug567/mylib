# 不准确，待继续调试
if [ "$ZSH_NAME" = "zsh" ]; then
    # zsh
    CUR_DIR=$(cd $(dirname ${0:a}); pwd)
    echo "current is zsh"
elif [ "$BASH_VERSION" != "" ]; then
    # bash
    CUR_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
    echo "current is bash"
else
    CUR_DIR=
    echo "current shell is unknown"
fi
