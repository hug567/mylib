# 1、copy：

- 复制属性：将一个函数、变量或类型的属性复制给另一个；
- 复制语法和语义属性，而不复制影响符号链接或可见性的属性，如别名、可见性或弱引用；
- 已弃用的属性和目标克隆属性也不会被复制；

```c
#define __copy(symbol)                   __attribute__((__copy__(symbol)))

// 原始函数，带有一组属性
__attribute__((noinline, pure)) int original_function(int x) {
  return x * 2;
}
// 具有与原始函数相同属性的新函数
__attribute__((copy(original_function))) int new_function(int x) {
  return x * 3;
}
```

# 2、alias：

```c

```

