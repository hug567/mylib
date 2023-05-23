#!/bin/bash
# change shell var in expect cmd
# 2023-05-23

function test_change_var() {
    echo "$FUNCNAME:-----------------------------"
    local age=18

    echo "before expect, age: $age"

    PS1="[host] $ "
    echo $PS1
    # save var to tmp file, can use mktemp to create tmp file
expect <<EOF
    set timeout 10
    exec touch /tmp/expect.txt
    exec echo 20 > /tmp/expect.txt
    expect "*\[host\] $ *"
EOF

    # read var value from tmp file
    age=$(cat /tmp/expect.txt)
    echo "after expect, age: $age"
}

function main() {
    test_change_var
}

main
