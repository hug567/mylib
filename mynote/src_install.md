## 1、源码安装glib-2.40：

```c
sudo apt install libffi-dev zlib1g-dev libmount-dev      //安装依赖
https://ftp.gnome.org/pub/gnome/sources/glib/2.40/       //下载glib-2.40
tar -xvf glib-2.40.0.tar.xz                              //解压
cd glib-2.40.0                                           //进入目录
vim glib/gdate.c                                         //编辑-2.40.0源码
#pragma GCC diagnostic push                              //2442行增加
#pragma GCC diagnostic ignored "-Wformat-nonliteral"     //2443行增加
#pragma GCC diagnostic pop                               //2554尾行增加
./configure                                              //默认配置
make                                                     //编译
sudo make install                                        //安装
```

## 2、源码安装qemu 4.0.0：

```C
sudo apt install pkg-config libpixman-1-dev              //安装依赖
https://download.qemu.org                                //下载qemu-4.0.0
tar -xvf qemu-4.0.0.tar.xz                               //解压
cd qemu-4.0.0                                            //进入
mkdir build && cd build                                  //新建build目录并进入
../configure                                             //默认配置
make                                                     //编译
sudo make install                                        //安装
qemu-img --version                                       //查看qemu版本
/usr/local/bin                                           //qemu install location



```

## 3、Q/A：

```C
/* 问题：symbol lookup error: /usr/lib/x86_64-linux-gnu/libatk-1.0.so.0:
 * undefined symbol: g_type_check_instance_is_fundamentally_a
 */
/* 解决：*/


```

