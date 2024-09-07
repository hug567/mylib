#!/usr/bin/awk -f
# run: ./test_bool.awk file.txt
# 学习：awk bool值
# 2024-09-06

BEGIN {
    main()
}

# 数值0和空字符串表示假
function fun_ret_false() {
    return 0
}

# 不是数值0和空字符串，均表示真
function fun_ret_true() {
    return 1
}

function test_bool() {
    print "[test_bool]: ------------------------------"

    # 函数返回布尔值
    if (fun_ret_true()) {
        print "function return true"
    }

    # 布尔值取反：!
    if (!fun_ret_false()) {
        print "function return false"
    }
}

function main() {
    test_bool()
}

{
}

END {
}
