## 1、配置环境

```c
sudo apt install qemu-utils qemu-kvm                     //安装qemu
qemu-img --version                                       //查看qemu版本
```

## 2、编译ucore：

```C
git clone https://github.com/chyyuu/ucore_os_lab.git     //下载ucore
cd cd ucore_os_lab/labcodes_answer/lab1_result/          //进入lab1目录
make                                                     //编译
make qemu                                                //运行
make clean                                               //删除编译生成文件
```

