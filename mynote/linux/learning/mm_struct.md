# 内存描述符

## 1、task_struct中的内存描述符：

```c
struct task_struct {
    /*
     * 用户进程：mm != NULL
     * 内核线程：mm == NULL
     */
    struct mm_struct *mm;
    /*
     * 用户进程：active_mm == mm
     * 内核线程：
     *   未运行时：active_mm == NULL
     *   运行时：active_mm == 上一个进程的内存描述符
     */
    struct mm_struct *active_mm;
};
```

# 2、常见缩写：

```bash
pfn：page frame number，页帧号（物理内存区域编号）
```

# 3、内存布局举例：

```bash
# 查看物理内存布局
cat /proc/iomem
# 查看进程用户空间内存布局
cat /proc/<pid>/maps
```

- aarc h64，48位虚址，4k页，4级页表：

```bash
       Start            End         Size   Use
 ------------------------------------------------
 0000000000000000 0000ffffffffffff  256TB  user
 ffff000000000000 ffffffffffffffff  256TB  kernel
```

## 1）、用户空间：

## 2）、内核空间：

```bash
       Start            End         Size   Use
 ------------------------------------------------
```

