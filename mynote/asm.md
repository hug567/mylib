## 1、编译汇编：

```C
sudo apt install nasm                                    //安装nasm
nasm -v                                                  //查看nasm版本
nasm -f elf64 hello.asm                                  //编译
ld -s -o hello hello.o                                   //链接
./hello                                                  //运行可执行文件
```

