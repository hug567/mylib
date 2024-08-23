# u-boot脚本：

# 1、基本概念：

- 1、语法与shell类似，源文件名称随意，如boot.cmd；
- 2、使用时需使用mkimage转换成二进制格式，如：

```bash
mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "U-Boot script" -d boot.cmd boot.scr
```

## 1）、u-boot添加自定义命令：

```bash
setenv mycmd "ping 192.168.0.13"
printenv mycmd
run mycmd
```

## 2）、多种启动方式：

```bash
# 若能从tftpserver下载指定镜像，则启动下载的镜像，否则按默认方式启动
setenv get_image_tftp "tftpboot 0x10000000 image-nothing.ub"
setenv myboot "if run get_image_tftp; then bootm 0x10000000; else boot; fi"
run myboot

# 无限循环尝试从tftpserver加载名为image-mkpart.ub的文件，若加载成功，则启动该镜像；若加载失败，睡眠3s后继续尝试加载
setenv get_image_loop "while true; do if tftpboot 0x10000000 image-mkpart.ub; then exit 0; else sleep 3; fi; done"
setenv myboot "if run get_image_loop; then bootm 0x10000000; fi"
run myboot
```

