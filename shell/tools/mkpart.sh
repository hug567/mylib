#!/bin/bash

function del_all_sd_part() {
    local dev=$1
    local part_num=$(fdisk -l $dev | grep "^$dev" | wc -l)

    umount_parts $mountpoint
    echo "cur part num is $part_num, will del all part"
    case $part_num in
        0)
            echo "part num is 0, no need del"
            ;;
        1)
            echo -e "d\nw\n" | fdisk $dev
            ;;
        2)
            echo -e "d\n1\nd\nw\n" | fdisk $dev
            ;;
        3)
            echo -e "d\n1\nd\n2\nd\nw\n" | fdisk $dev
            ;;
        4)
            echo -e "d\n1\nd\n2\nd\n3\nd\nw\n" | fdisk $dev
            ;;
        *)
            echo "unsupported del part num: $part_num"
            exit 1
    esac
}

# make part in script
function make_part () {
    local dev="/dev/mmcblk0"

    echo -e "n\np\n1\n2048\n2099199\nn\np\n2\n2099200\n23070719\nn\np\n3\n23070720\n\nw\n" | fdisk $dev
}

function main() {
    echo "hello"
}

main $*
