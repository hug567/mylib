#!/bin/bash

# 在当前脚本source其他两个脚本，这些脚本中都有同名函数，测试当执行不同脚本中的
# 函数时，会执行那个函数

# 结论：执行的都是main.sh中的myname
# 脚本执行结果：
#   [main.sh] myname: ./main.sh
#   [main.sh] myname: ./main.sh
#   [main.sh] myname: ./main.sh

source ./test01.sh
source ./test02.sh

function myname() {
    echo "[main.sh] myname: $0"
}

function main() {
    myname
    test01_main
    test02_main
}

main
