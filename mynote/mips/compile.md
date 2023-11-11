# 1、编译MIPS用户程序：

```bash
# Ubuntu 20.04
# 安装交叉编译器
sudo apt install gcc-mips-linux-gnu
mips-linux-gnu-gcc --version

# 编译
mips-linux-gnu-gcc -mfp32 -march=R2000 hello.c

# qemu运行mips程序
qemu-mips -L /usr/mips-linux-gnu ./a.out
```

