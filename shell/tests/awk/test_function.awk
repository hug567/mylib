#!/usr/bin/awk -f
# run: ./test_function.awk file.txt

BEGIN {
    # BEGAIN中代码只在脚本开始时执行一次
    # 调用main函数
    main()
}

END {
}

# 函数无参数和返回值
function test_hello() {
    print "hello awk"
}

# 函数有多个参数
function test_name(name, age) {
    # 使用函数参数
    print "person name: " name ", age: " age
}

# 函数有多个参数和返回值
function test_add(a, b) {
    sum = a + b
    return sum
}

function main() {
    # 调用函数
    test_hello()
    # 调用带参函数
    test_name("Bob", 19)
    # 调用带参函数，并获取返回值
    print "3 + 5 = " test_add(3, 5)
}

# 处理输入文件的每一行时，均执行一遍此处的代码
{
    #main()
}
