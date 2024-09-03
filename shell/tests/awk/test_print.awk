#!/usr/bin/awk -f
# run: ./test_print.awk file.txt

BEGIN {
    print "begin awk script......"
}

END {
    print "end awk script......"
}

{
    # 使用默认分隔符空格分割每行，打印分割后的第一列
    # $0: 整行内容
    # $1/$2/$3...: 第1/2/3...列
    # NF: 列数
    # $NF: 最后一列
    # NR: 行号
    print $0
}
