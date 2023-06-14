## 1、入门：

```c
config ARM_L1_CACHE_SHIFT
        int
        default 7 if ARM_L1_CACHE_SHIFT_7
        default 6 if ARM_L1_CACHE_SHIFT_6
        default 5  // 1<<5=32

/* vexpress-a9: */
CONFIG_CPU_V7=y
CONFIG_L1_CACHE_SHIFT_6=y
CONFIG_L1_CACHE_SHIFT=6  // 1<<6=64

./arch/arm/include/asm/cache.h:8:#define L1_CACHE_SHIFT  CONFIG_ARM_L1_CACHE_SHIFT
./arch/arm64/include/asm/cache.h:32:#define L1_CACHE_SHIFT  7  // 1<<7=128

#define L1_CACHE_BYTES         (1 << L1_CACHE_SHIFT)
#define NET_SKB_PAD       max(32, L1_CACHE_BYTES)


```

