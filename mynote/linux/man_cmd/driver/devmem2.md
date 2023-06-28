# 1、命令参数：

```bash
Usage:  devmem2 { address } [ type [ data ] ]
        address : memory address to act upon
        type    : access operation type : [b]yte, [h]alfword, [w]ord
        data    : data to be written
```

# 2、常见用法：

```bash
# 读物理地址
devmem2 0x2310000                   # 默认读字数据(w)
devmem2 0x2310000 b
devmem2 0x2310000 h
devmem2 0x2310000 w

# 写物理地址
devmem2 0x2310000 w 0xffff0000
```

