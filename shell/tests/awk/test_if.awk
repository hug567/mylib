#!/usr/bin/awk -f
# run: ./test_if.awk file.txt
# 学习：awk if语句
# 2024-09-06

BEGIN {
    main()
}

function test_if() {
    print "[test_if]: --------------------------------"

    num = 10
    # if语句
    if (num > 5) {
        print "num > 5"
    }

    # if-else语句
    if (num > 15) {
        print "num > 15"
    } else {
        print "num <= 15"
    }

    # if-else if-else语句
    if (num > 20) {
        print "num > 20"
    } else if (num > 10) {
        print "10 < num <= 20"
    } else {
        print "num <= 10"
    }
}

function main() {
    test_if()
}

{
}

END {
}
