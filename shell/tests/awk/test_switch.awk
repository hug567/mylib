#!/usr/bin/awk -f
# run: ./test_switch.awk file.txt
# 学习：awk switch语句
# 2024-09-07

BEGIN {
    main()
}

function test_switch() {
    print "[test_switch]: ----------------------------"
}

function main() {
    test_switch()
}

{
}

END {
}
