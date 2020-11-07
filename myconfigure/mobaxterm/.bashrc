#!/bin/bash
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"
SKYBLUE="\033[36m"
WHITE="\033[37m"
RESET="\033[0m"

alias cls='clear'
alias lsa='ls -a'

export PS1="${BLUE}[\u${RED}@${BLUE}\h]: ${YELLOW}\w\n ${RED}$ ${RESET}"
