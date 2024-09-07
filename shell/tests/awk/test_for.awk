#!/usr/bin/awk -f
# run: ./test_for.awk file.txt
# 学习：awk for语句
# 2024-09-07

BEGIN {
    main()
}

function test_for() {
    print "[test_for]: -------------------------------"

    # for语句
    for (i = 0; i < 5; i++) {
        print "i: " i
    }

    # break语句
    for (i = 0; i < 5; i++) {
        if (i > 3) {
            break
        }
        print "[break] i: " i
    }

    # continue语句
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            continue
        }
        print "[continue] i: " i
    }
}

function main() {
    test_for()
}

{
}

END {
}
