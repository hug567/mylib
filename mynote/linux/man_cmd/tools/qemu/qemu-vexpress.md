# 1、vexpress挂载虚拟磁盘设备：

```bash
# 创建img文件：
qemu-img create -f qcow2 myimg.qcow2 128M
# 虚拟机创建设备：
-drive format=qcow2,file=myimg.qcow2
```

