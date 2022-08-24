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

