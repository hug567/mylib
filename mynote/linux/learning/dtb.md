## 1、参考文档：
Devicetree Specification：https://devicetree-specification.readthedocs.io/en/v0.2/index.html
linux设备树dtb格式：https://www.cnblogs.com/downey-blog/p/10485529.html

## 2、dtb文件结构：
| fdt文件结构：            |
| ------------------------ |
| struct ftd_header        |
| memory reservation block |
| structure block          |
| string block             |

## 3、文件头：
* dtb header：
```c
struct fdt_header {
	fdt32_t magic;			 /* magic word FDT_MAGIC */
	fdt32_t totalsize;		 /* total size of DT block */
	fdt32_t off_dt_struct;		 /* offset to structure */
	fdt32_t off_dt_strings;		 /* offset to strings */
	fdt32_t off_mem_rsvmap;		 /* offset to memory reserve map */
	fdt32_t version;		 /* format version */
	fdt32_t last_comp_version;	 /* last compatible version */

	/* version 2 fields below */
	fdt32_t boot_cpuid_phys;	 /* Which physical CPU id we're
						booting on */
	/* version 3 fields below */
	fdt32_t size_dt_strings;	 /* size of the strings block */

	/* version 17 fields below */
	fdt32_t size_dt_struct;		 /* size of the structure block */
};
```

```shell
# vim查看二进制文件：
vim -b file.dtb
:%!xxd
```

* 以大端dtb文件为例，文件头大小为40字节：
```c
00000000: d00d feed 0000 23dd 0000 0048 0000 2194
00000010: 0000 0028 0000 0011 0000 0010 0000 0000
00000020: 0000 0249 0000 214c
```
* 1、魔数：0xd00dfeed (大端)
* 2、文件大小：0x000023dd = 9181字节
* 3、结构块偏移：0x00000048
* 4、字符串块偏移：0x00002194 (以\0分割字符串)
* 5、内存保留区域块偏移：0x00000028 (紧跟dtb头部)
* 6、版本：0x00000011 = 17
* 7、最老兼容版本：0x00000010 = 16
* 8、启动CPU编号：0x00000000 = 0，仅在版本2中有效
* 9、字符串块大小：0x00000249 = 585字节
* 10、结构块大小：0x0000214c = 8524字节

## 4、内存保留区域：

* 数据结构：

```c
struct fdt_reserve_entry {
    uint64_t address;
    uint64_t size;
};
```

* dts描述：

```c
/dts-v1/;
/memreserve/ 0xA00000  0x10000    //64K
```

* 大端dtb举例：

```c
00000020: 0000 0249 0000 214c 0000 0000 00a0 0000
00000030: 0000 0000 0001 0000
```
内存保留区域块偏移：0x28
内存保留区域起始地址：0xa00000
内存保留区域大小：0x1000

## 5、结构块：

每个节点都会被描述为一个struct，节点之间可以嵌套，因此也会有嵌套的struct。

* 节点开始信号：OF_DT_BEGIN_NODE = 0x00000001；
* 节点名：字符串，以\0结束
* 可选对齐字节：不定大小；
* 属性：
    * 属性开始信号：OF_DT_PROP = 0x00000003；
    * 属性大小：32字节
    * 属性名在字符串块中的偏移：32字节
    * 属性中的值：长度由属性大小指定
* 递归对子节点进行描述
* 节点结束信号：OF_DT_END_NODE = 0x00000002；
* 结构块结束信号：0x00000009
* 例：
```c
000013f0: 0000 0001 7561 7274 4034 3462 3534 3030  ....uart@44b5400
00001400: 3000 0000 0000 0003 0000 0021 0000 0021  0..........!...!
00001410: 736e 7073 2c64 772d 6170 622d 7561 7274  snps,dw-apb-uart
00001420: 0061 726d 2c64 7738 3235 302c 7561 7274  .arm,dw8250,uart
00001430: 0000 0000 0000 0003 0000 0010 0000 0059  ...............Y
00001440: 0000 0000 44b5 4000 0000 0000 0000 1000  ....D.@.........
00001450: 0000 0003 0000 0004 0000 00bf 0000 1000  ................
00001460: 0000 0003 0000 0004 0000 002c 0000 0001  ...........,....
00001470: 0000 0003 0000 000c 0000 005d 0000 0029  ...........]...)
00001480: 0000 0060 0000 0001 0000 0003 0000 0000  ...`............
00001490: 0000 019a 0000 0002
```
