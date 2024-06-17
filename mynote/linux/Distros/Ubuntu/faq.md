# Ubuntu 22.04：

## 1、不能识别usb转串口ch341：

```bash
sudo dmesg | grep ttyUSB | tail

[884887.088468] ch341-uart ttyUSB0: ch341-uart converter now disconnected from ttyUSB0
```

解决：卸载brltty

```bash
sudo apt remove brltty
```

## 2、ubuntu 18.04启动后停在grub：

```bash
# 手动启动系统:
ls (hd0,gpt3)/
set root=(hd0,gpt3)
set prefix=(hd0,gpt3)/boot/grub
linux /vmlinuz root=/dev/sda3
initrd /initrd.img
boot

# 成功进入系统后连接网络，修复grub：
sudo add-apt-repository ppa:yannubuntu/boot-repair
sudo apt update
sudo apt install boot-repair
sudo boot-repair
```

