# arm32 cache：

- cache：将cache中数据同步到内存；

- invalidate：是cache中数据无效，后续读取将从内存获取数据；

- flash：clean + invalidata，非arm原生，一些系统提供的组合操作，常用于DMA；

- icache：指令cache；

- dcache：数据cache；

```c
// 在armv7裸核程序中验证可成功将写数据从cache同步到内存，pa：内存物理地址
static inline void flush_cache(void *pa)
{
    asm volatile("mcr p15, 0, %0, c7, c14, 1"::"r"(pa));
}
```

# aarch64 cache：