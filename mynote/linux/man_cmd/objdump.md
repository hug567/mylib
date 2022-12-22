# 1、常见用法：

```bash
objdump -T xxx.so    # 查看动态符号表
    -d    # 反汇编代码段
    -S    # 反汇编代码中插入源码

# 常用命令：
objdump -d -S vmlinux > vmlinux.asm
```
