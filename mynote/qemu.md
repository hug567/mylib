## 1、基本命令
----
```c
-cpu         //
-M vexpress-a9                              //模拟vexpress-a9单板
-M help                                     //获取支持的所有单板
-m 512M                                     //内存512M
-kernel ./arch/arm/boot/zImage              //内核镜像路径
-nographic                                  //不使用图形化界面，只使用串口
-append "console=ttyAMA0"                   //串口设备是哪个tty
```
## 2、qemu支持网络
----
```c
/* 首先内核中支持tap/tuns设备：CONFIG_TUN */
Device Drivers  ---> 
     Networking support  --->
        [M] Universal TUN/TAP device driver support
/* Kconfig位置: CONFIG_TUN */
linux-4.15/drivers/net/Kconfig

```

## 3、qemu help

```c
qemu-system-arm -machine help    //查看支持的开发板
qemu-system-arm -machine virt -cpu help  //查看开发板支持的CPU
qemu-system-arm -machine vexpress-a9 -nic model=help  //查看支持的nic模式
qemu-system-x86_64 -device help    //查看支持的设备模块
```