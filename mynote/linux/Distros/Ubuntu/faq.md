# Ubuntu 22.04：

## 1）、不能识别usb转串口ch341：

```bash
sudo dmesg | grep ttyUSB | tail

[884887.088468] ch341-uart ttyUSB0: ch341-uart converter now disconnected from ttyUSB0
```

解决：卸载brltty

```bash
sudo apt remove brltty
```

