### 1、Linux相关缩写：
```
EABI：Embedded Application Binary Interface，嵌入式二进制应用程序接口
armel：arm eabi little endian，软件浮点
armhf：arm hard float，硬件浮点
```

### 2、常用gcc：
```
arm-linux-gnueabi-gcc    //armel软件浮点架构，sudo apt install gcc-arm-linux-gnueabi
arm-linux-gnueabihf-gcc   //armhf硬件浮点架构，sudo apt install gcc-arm-linux-gnueabihf
arm-none-linux-gnueabi-gcc    //编译ARM架构的u-boot、Linux内核、linux应用等程序
```