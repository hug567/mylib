## 1、链接脚本：

 作用：主要用于规定如何把输入文件内的section放入输出文件内, 并控制输出文件内各部分在程序地址空间内的布局。

```c
//查看默认链接脚本
ld --verbose
-T    //指定自定义链接脚本
```

```c
ENTRY(SYMBOL)             //将符号SYMBOL设为程序入口地址
INCLUDE filename          //包含名为filename的链接脚本，搜索路径由-L指定，最大深度为10
INPUT(files)              //文件files作为输入文件，搜索路径由-L指定，或由命令行-lfile指定
OUTPUT_ARCH(BFDARCH)      //设置输出文件的架构
SECTIONS{}                //描述section链接方式







```

