#!/usr/bin/awk -f
# run: ./test_awk.awk file.txt
# 学习：awk变量
# 2024-09-05

# awk中只有函数参数是局部变量，其他的均是全局变量，从变量定义的位置开始生效，
# 直到脚本结束

BEGIN {
    print "[BEGIN]: ----------------------------------"

    # 在BEGIN中定义全局变量
    g_age = 18

    main()
}

# 函数中局部变量
function test_local_var(num, name) {
    print "[test_local_var]: -------------------------"

    # 只有函数参数是局部变量
    print "num: " num
    print "name: " name

    # 在函数中定义的参数也是全局变量
    g_height = 180
}

function test_global_var_use() {
    print "[test_global_var_use]: --------------------"
    # 使用全局变量
    print "g_age: " g_age
    print "g_height: " g_height
}

function test_global_var_change() {
    # 修改全局变量
    g_age = g_age + 1
    # 修改在其他函数中定义的全局变量
    g_height = g_height + 1
}

function main() {
    test_local_var(10, "Tom")
    test_global_var_use()
    test_global_var_change()
    test_global_var_use()
}

{
    # 逐行处理代码块中也可以定义变量，且是全局变量
    sum = sum + 1
}

END {
    print "[END]: ------------------------------------"
    # 引用主代码中定义的变量
    print "sum: " sum
}
