#!/bin/bash

usage()
{
    echo "Usage:"
    echo "  $0                show 256 color"
    echo "  $0 <fg> <bg>      show example width <fg><bg>"
}

# (index, r, g, b) with hex
g_color256=(
    '  0 00 00 00'
    '  1 80 00 00'
    '  2 00 80 00'
    '  3 80 80 00'
    '  4 00 00 80'
    '  5 80 00 80'
    '  6 00 80 80'
    '  7 c0 c0 c0'
    '  8 80 80 80'
    '  9 ff 00 00'
    ' 10 00 ff 00'
    ' 11 ff ff 00'
    ' 12 00 00 ff'
    ' 13 ff 00 ff'
    ' 14 00 ff ff'
    ' 15 ff ff ff'

    ' 16 00 00 00'
    ' 17 00 00 5f'
    ' 18 00 00 87'
    ' 19 00 00 af'
    ' 20 00 00 df'
    ' 21 00 00 ff'
    ' 22 00 5f 00'
    ' 23 00 5f 5f'
    ' 24 00 5f 87'
    ' 25 00 5f af'
    ' 26 00 5f df'
    ' 27 00 5f ff'
    ' 28 00 87 00'
    ' 29 00 87 5f'
    ' 30 00 87 87'
    ' 31 00 87 af'
    ' 32 00 87 df'
    ' 33 00 87 ff'
    ' 34 00 af 00'
    ' 35 00 af 5f'
    ' 36 00 af 87'
    ' 37 00 af af'
    ' 38 00 af df'
    ' 39 00 af ff'
    ' 40 00 df 00'
    ' 41 00 df 5f'
    ' 42 00 df 87'
    ' 43 00 df af'
    ' 44 00 df df'
    ' 45 00 df ff'
    ' 46 00 ff 00'
    ' 47 00 ff 5f'
    ' 48 00 ff 87'
    ' 49 00 ff af'
    ' 50 00 ff df'
    ' 51 00 ff ff'

    ' 52 5f 00 00'
    ' 53 5f 00 5f'
    ' 54 5f 00 87'
    ' 55 5f 00 af'
    ' 56 5f 00 df'
    ' 57 5f 00 ff'
    ' 58 5f 5f 00'
    ' 59 5f 5f 5f'
    ' 60 5f 5f 87'
    ' 61 5f 5f af'
    ' 62 5f 5f df'
    ' 63 5f 5f ff'
    ' 64 5f 87 00'
    ' 65 5f 87 5f'
    ' 66 5f 87 87'
    ' 67 5f 87 af'
    ' 68 5f 87 df'
    ' 69 5f 87 ff'
    ' 70 5f af 00'
    ' 71 5f af 5f'
    ' 72 5f af 87'
    ' 73 5f af af'
    ' 74 5f af df'
    ' 75 5f af ff'
    ' 76 5f df 00'
    ' 77 5f df 5f'
    ' 78 5f df 87'
    ' 79 5f df af'
    ' 80 5f df df'
    ' 81 5f df ff'
    ' 82 5f ff 00'
    ' 83 5f ff 5f'
    ' 84 5f ff 87'
    ' 85 5f ff af'
    ' 86 5f ff df'
    ' 87 5f ff ff'
    ' 88 87 00 00'
    ' 89 87 00 5F'
    ' 90 87 00 87'
    ' 91 87 00 AF'
    ' 92 87 00 D7'
    ' 93 87 00 FF'
    ' 94 87 5F 00'
    ' 95 87 5F 5F'
    ' 96 87 5F 87'
    ' 97 87 5F AF'
    ' 98 87 5F D7'
    ' 99 87 5F FF'
    '100 87 87 00'
    '101 87 87 5F'
    '102 87 87 87'
    '103 87 87 AF'
    '104 87 87 D7'
    '105 87 87 FF'
    '106 87 AF 00'
    '107 87 AF 5F'
    '108 87 AF 87'
    '109 87 AF AF'
    '110 87 AF D7'
    '111 87 AF FF'
    '112 87 DF 00'
    '113 87 D7 5F'
    '114 87 D7 87'
    '115 87 D7 AF'
    '116 87 D7 D7'
    '117 87 D7 FF'
    '118 87 FF 00'
    '119 87 FF 5F'
    '120 87 FF 87'
    '121 87 FF AF'
    '122 87 FF D7'
    '123 87 FF FF'

    '124 AF 00 00'
    '125 AF 00 5F'
    '126 AF 00 87'
    '127 AF 00 AF'
    '128 AF 00 D7'
    '129 AF 00 FF'
    '130 AF 5F 00'
    '131 AF 5F 5F'
    '132 AF 5F 87'
    '133 AF 5F AF'
    '134 AF 5F D7'
    '135 AF 5F FF'
    '136 AF 87 00'
    '137 AF 87 5F'
    '138 AF 87 87'
    '139 AF 87 AF'
    '140 AF 87 D7'
    '141 AF 87 FF'
    '142 AF AF 00'
    '143 AF AF 5F'
    '144 AF AF 87'
    '145 AF AF AF'
    '146 AF AF D7'
    '147 AF AF FF'
    '148 AF D7 00'
    '149 AF D7 5F'
    '150 AF D7 87'
    '151 AF D7 AF'
    '152 AF D7 D7'
    '153 AF D7 FF'
    '154 AF FF 00'
    '155 AF FF 5F'
    '156 AF FF 87'
    '157 AF FF AF'
    '158 AF FF D7'
    '159 AF FF FF'

    '160 D7 00 00'
    '161 D7 00 5F'
    '162 D7 00 87'
    '163 D7 00 AF'
    '164 D7 00 D7'
    '165 D7 00 FF'
    '166 D7 5F 00'
    '167 D7 5F 5F'
    '168 D7 5F 87'
    '169 D7 5F AF'
    '170 D7 5F D7'
    '171 D7 5F FF'
    '172 D7 87 00'
    '173 D7 87 5F'
    '174 D7 87 87'
    '175 D7 87 AF'
    '176 D7 87 D7'
    '177 D7 87 FF'
    '178 D7 AF 00'
    '179 D7 AF 5F'
    '180 D7 AF 87'
    '181 D7 AF AF'
    '182 D7 AF D7'
    '183 D7 AF FF'
    '184 D7 D7 00'
    '185 D7 D7 5F'
    '186 D7 D7 87'
    '187 D7 D7 AF'
    '188 D7 D7 D7'
    '189 D7 D7 FF'
    '190 D7 FF 00'
    '191 D7 FF 5F'
    '192 D7 FF 87'
    '193 D7 FF AF'
    '194 D7 FF D7'
    '195 D7 FF FF'

    '196 FF 54 54'
    '197 FF 00 5F'
    '198 FF 00 87'
    '199 FF 00 AF'
    '200 FF 00 D7'
    '201 FF 54 FF'
    '202 FF 5F 00'
    '203 FF 5F 5F'
    '204 FF 5F 87'
    '205 FF 5F AF'
    '206 FF 5F D7'
    '207 FF 5F FF'
    '208 FF 87 00'
    '209 FF 87 5F'
    '210 FF 87 87'
    '211 FF 87 AF'
    '212 FF 87 D7'
    '213 FF 87 FF'
    '214 FF AF 00'
    '215 FF AF 5F'
    '216 FF AF 87'
    '217 FF AF AF'
    '218 FF AF D7'
    '219 FF AF FF'
    '220 FF D7 00'
    '221 FF D7 5F'
    '222 FF D7 87'
    '223 FF D7 AF'
    '224 FF D7 D7'
    '225 FF D7 FF'
    '226 FF FF 54'
    '227 FF FF 5F'
    '228 FF FF 87'
    '229 FF FF AF'
    '230 FF FF D7'
    '231 FF FF FF'

    '232 08 08 08'
    '233 12 12 12'
    '234 1c 1c 1c'
    '235 26 26 26'
    '236 30 30 30'
    '237 3a 3a 3a'
    '238 44 44 44'
    '239 4e 4e 4e'
    '240 58 58 58'
    '241 60 60 60'
    '242 66 66 66'
    '243 76 76 76'
)

g_num=0
si=0
# $1: index
# $2: r
# $3: g
# $4: b
showBackgroundColor()
{
    printf "%4d: \x1b[48;2;%s;%s;%sm%6s\x1b[0m" $1 $2 $3 $4 " "
    let si+=1
    if [ $si == $g_num ]; then
        printf "\n"
        let si=0
    fi
}

getColorByIndex()
{
    index=$1
    color='ff ff ff' # default(white)
    for col in "${g_color256[@]}"; do
        color=($col)
        i=${color[0]}
        cr=${color[1]}
        cg=${color[2]}
        cb=${color[3]}
        if [ $i == $index ]; then
            echo "$cr $cg $cb"
            return
        fi
    done
}

# $1: fg color index (0-255)
# $2: bg color index (0-255)
showDemoColor()
{
    fg=$(getColorByIndex $1)
    fgr=$(echo $fg | awk -F " " '{print $1}')
    fgg=$(echo $fg | awk -F " " '{print $2}')
    fgb=$(echo $fg | awk -F " " '{print $3}')
    fgstr=$(printf "\x1b[38;2;%s;%s;%sm" $((16#${fgr})) $((16#${fgg})) $((16#${fgb})))
    bg=$(getColorByIndex $2)
    bgr=$(echo $bg | awk -F " " '{print $1}')
    bgg=$(echo $bg | awk -F " " '{print $2}')
    bgb=$(echo $bg | awk -F " " '{print $3}')
    bgstr=$(printf "\x1b[48;2;%s;%s;%sm" $((16#${bgr})) $((16#${bgg})) $((16#${bgb})))
    hint=$(printf "[fg=%03d,bg=%03d]: " $1 $2)
    screen_width=$(stty size | awk -F " " '{print $2}')
    let left_width=$screen_width-${#hint}
    code=""
    for i in $(seq 1 `expr $left_width - 10`)
    do
        code="x$code"
    done
    printf "\x1b[0m${hint}${fgstr}${bgstr}${code}\x1b[0m\n"
}

show256Color()
{
    g_i=0
    for col in "${g_color256[@]}"; do
        color=($col)
        num=${color[0]}
        cr=${color[1]}
        cg=${color[2]}
        cb=${color[3]}
        if [ $num == "232" ]; then
            printf "\n"
        fi
        showBackgroundColor $num $((16#$cr)) $((16#$cg)) $((16#$cb))
        if [ $g_i -lt "16" ]; then
            g_num=8
        else
            g_num=6
        fi
        if [ $num == "15" ]; then
            printf "\n"
        fi
        let g_i+=1
    done
}

##### main #####################################################################

if [[ $# != '0' && $# != '2' || $1 == '-h' ]]; then
    usage
    exit
fi

if [ $# == '0' ]; then
    show256Color
elif [ $# == '2' ]; then
    showDemoColor $1 $2
else
    usage
fi
