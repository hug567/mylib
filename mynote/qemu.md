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