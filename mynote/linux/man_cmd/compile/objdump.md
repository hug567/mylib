# 1、命令参数：

```bash
objdump -T xxx.so    # 查看动态符号表
    -d                       # 反汇编代码段
    -S                       # 反汇编代码中插入源码
    -r                       # 显示文件中的重定位项
    -l                       # 在输出中包含行号和文件名
    -h                       # 显示节头信息
    -t                       # 打印符号表
    -T                       # 打印动态符号表
    -j <seg>                 # 反汇编指定段
```

# 2、常见用法：
```bash
# 常用命令：
objdump -dS vmlinux > vmlinux.asm                # 反汇编代码并插入源码
objdump -dSrl vmlinux > vmlinux.asm              # 反汇编并插入源码、文件和行号
objdump -h vmlinux                               # 查看节头信息
# 查看有哪些段
objdump -h vmlinux
# 反汇编指定段
objdump -d -S -j .init.text vmlinux > vmlinux_init_text.asm
```
