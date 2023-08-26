# arm32 barrier：

## 1、dmb：

- Data Memory Barrier，数据内存屏障， 仅当所有在dmb前面的存储器访问指令都执行完毕后，才提交在它后面的存储器访问操作；

```c
dmb
dmb sy
dmb st
dmb ish
dmb ishst
dmb nsh
dmb nshst
dmb osh
dmb oshst
```



## 2、dsb：

- Data Synchronization Barrier，数据同步隔离，比dmb严格，仅当所有在dsb前面的存储器访问操作都执行完毕后，才执行在它后面的指令；

```c
dsb
dsb sy
dsb st
dsb ish
dsb ishst
dsb nsh
dsb nshst
dsb osh
dsb oshst
```




## 3、isb：

- Instruction Synchronization Barrier，指令同步隔离，最严格，isb会清洗流水线，以保证所有它前面的指令都执行完毕之后，才执行它后面的指令；

```c
isb
isb sy
```



# aarch64 barrier：