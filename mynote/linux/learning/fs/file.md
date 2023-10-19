# 1、struct file：

```c
// include/linux/fs.h
struct file {
    const struct file_operations *f_op;
}
```

