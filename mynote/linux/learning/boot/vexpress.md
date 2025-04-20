# vexpress开发板信息：

## 1、内存：

```bash
~ # cat /proc/iomem
00000000-03ffffff : 0.flash flash@0
04000000-07ffffff : 0.flash flash@0
09000000-09000fff : pl011@9000000
  09000000-09000fff : 9000000.pl011 pl011@9000000
09010000-09010fff : pl031@9010000
  09010000-09010fff : rtc-pl031
09030000-09030fff : pl061@9030000
40000000-4fffffff : System RAM
  40008000-40cfffff : Kernel code
  40e00000-40eea7cf : Kernel data
```

