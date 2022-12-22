# 1、常见用法：

```bash
# 将地址转换为函数名和行数
addr2line
    -e <file>                        # 指定输入文件，默认为a.out
    -f                               # 打印函数名

# 常用例子
addr2line ffff800010d0b6a8 -f -e vmlinux

```
