#!/bin/bash

if [ "$ZSH_NAME" = "zsh" ]; then
    # zsh
    CUR_DIR=$(cd $(dirname ${0:a}); pwd)
elif [ "$BASH_VERSION" != "" ]; then
    # bash
    CUR_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
else
    CUR_DIR=
fi

alias flash-zynq="$CUR_DIR/flash_zynq.sh"
