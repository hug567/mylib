# 1、虚存管理相关变量：

```c
//mm/vmalloc.c
vmap_area_root              //管理已使用的vmalloc虚存区域
free_vmap_area_root         //管理还未使用的vmalloc虚存区域
```

