# arm32 cache：

- cache：将cache中数据同步到内存；

- invalidate：是cache中数据无效，后续读取将从内存获取数据；

- flash：clean + invalidata，非arm原生，一些系统提供的组合操作，常用于DMA；

- icache：指令cache；

- dcache：数据cache；



# aarch64 cache：