#!/bin/bash

g_num=0

# $1: index
# $2: r
# $3: g
# $4: b
si=0
showBackgroundColor()
{
    printf "%4d: \x1b[48;2;%s;%s;%sm%6s\x1b[0m" $1 $2 $3 $4 " "
    let si+=1
    if [ $si == $g_num ]; then
        printf "\n"
        let si=0
    fi
}

# (r, g, b) with hex
color256=(
    '00 00 00' #   0
    '80 00 00' #   1
    '00 80 00' #   2
    '80 80 00' #   3
    '00 00 80' #   4
    '80 00 80' #   5
    '00 80 80' #   6
    'c0 c0 c0' #   7
    '80 80 80' #   8
    'ff 00 00' #   9
    '00 ff 00' #  10
    'ff ff 00' #  11
    '00 00 ff' #  12
    'ff 00 ff' #  13
    '00 ff ff' #  14
    'ff ff ff' #  15
    '00 00 00' #  16
    '00 00 5f' #  17
    '00 00 87' #  18
    '00 00 af' #  19
    '00 00 df' #  20
    '00 00 ff' #  21
    '00 5f 00' #  22
    '00 5f 5f' #  23
    '00 5f 87' #  24
    '00 5f af' #  25
    '00 5f df' #  26
    '00 5f ff' #  27
    '00 87 00' #  28
    '00 87 5f' #  29
    'ee ee ee' # 255
)

index=0
for i in "${color256[@]}"; do
    color=($i)
    cr=${color[0]}
    cg=${color[1]}
    cb=${color[2]}
    showBackgroundColor $index $((16#$cr)) $((16#$cg)) $((16#$cb))
    if [ $index -lt "16" ]; then
        g_num=8
    else
        g_num=6
    fi
    if [ $index == "15" ]; then
        printf "\n"
    fi
    let index+=1
done
printf "\n"
