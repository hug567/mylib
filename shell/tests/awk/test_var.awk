#!/usr/bin/awk -f
# run: ./test_awk.awk file.txt
# 学习：awk变量
# 2024-09-05

BEGIN {
    # 在BEGAIN中定义全局变量
    g_age = 18

    main()
}

# 函数中局部变量
function test_local_var() {
    # 定义及引用整形变量
    num = 10
    print "num: " num

    # 定义及引用字符串变量
    name = "Tom"
    print "name: " name
}

function test_global_var_use() {
    # 使用全局变量
    print "g_age: " g_age
}

function test_global_var_change() {
    # 修改全局变量
    g_age = g_age + 1
}

function main() {
    test_local_var()
    test_global_var_use()
    test_global_var_change()
    test_global_var_use()
}

{
    # 逐行处理代码块中也可以定义变量，且是全局变量
    sum = sum + 1
}

END {
    # 引用主代码中定义的变量
    print "sum: " sum
}
