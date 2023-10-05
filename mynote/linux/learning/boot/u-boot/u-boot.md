# 1、u-boot 64字节头：

```bash
#define IH_MAGIC        0x27051956      /* Image Magic Number           */
#define IH_NMLEN                32      /* Image Name Length            */

struct legacy_img_hdr {
        uint32_t        ih_magic;       /* Image Header Magic Number    */
        uint32_t        ih_hcrc;        /* Image Header CRC Checksum    */
        uint32_t        ih_time;        /* Image Creation Timestamp     */
        uint32_t        ih_size;        /* Image Data Size              */
        uint32_t        ih_load;        /* Data  Load  Address          */
        uint32_t        ih_ep;          /* Entry Point Address          */
        uint32_t        ih_dcrc;        /* Image Data CRC Checksum      */
        uint8_t         ih_os;          /* Operating System             */
        uint8_t         ih_arch;        /* CPU architecture             */
        uint8_t         ih_type;        /* Image Type                   */
        uint8_t         ih_comp;        /* Compression Type             */
        uint8_t         ih_name[IH_NMLEN];      /* Image Name           */
};

=> md 0x60003000
60003000: 56190527 ca60a28f ac4a6b63 8667aa00  '..V..`.ckJ...g.
60003010: 00300060 40300060 502d62aa 00021605  `.0.`.0@.b-P....
60003020: 00000000 00000000 00000000 00000000  ................
60003030: 00000000 00000000 00000000 00000000  ................

ih_os   = 0x05 : linux
ih_arch = 0x16 : arm64
ih_type = 0x02 : kernel
ih_comp = 0x00 : none ?
          0x02 : gzip
```

## 2、u-boot内存分布：

```c
CONFIG_ENV_ADDR=0x04000000  // 环境变量存储地址
CONFIG_ENV_OFFSET 
CONFIG_ENV_SIZE=0x40000
CONFIG_ENV_SECT_SIZE=0x40000
CONFIG_SYS_LOAD_ADDR=0x40200000  //
CONFIG_DEBUG_UART_BASE=0x9000000
```

## 3、u-boot传递给kernel的信息：

- 内核地址：
- initrd地址：
- dtb地址：x0
- cmdline：










