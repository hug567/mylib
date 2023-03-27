# 1、常见用法：

```bash
objdump -T xxx.so    # 查看动态符号表
    -d    # 反汇编代码段
    -S    # 反汇编代码中插入源码
    -r    # 显示文件中的重定位项
    -l    # 在输出中包含行号和文件名
    -h    # 显示节头信息
    -t    # 打印符号表
    -T    # 打印动态符号表

# 常用命令：
objdump -d -S vmlinux > vmlinux.asm              # 反汇编代码并插入源码
objdump -d -S -r -l vmlinux > vmlinux.asm        # 反汇编并插入源码、文件和行号
objdump -h vmlinux                               # 查看节头信息
```
