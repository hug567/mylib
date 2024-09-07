#!/usr/bin/awk -f
# run: ./test_while.awk file.txt
# 学习：awk while语句
# 2024-09-07

BEGIN {
    main()
}

# while语句中也可结合break, continue语句
function test_while() {
    print "[test_while]: -----------------------------"

    # while语句
    i = 0
    while (i < 5) {
        print "[while] i: " i
        i++
    }

    # do-while语句
    i = 5
    do {
        print "[do-while] i: " i
        i--
    } while (i > 0)
}

function main() {
    test_while()
}

{
}

END {
}
