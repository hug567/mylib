# 1、copy：

- 复制属性：将一个函数、变量或类型的属性复制给另一个；
- 复制语法和语义属性，而不复制影响符号链接或可见性的属性，如别名、可见性或弱引用；
- 已弃用的属性和目标克隆属性也不会被复制；

```c
#define __copy(symbol) __attribute__((__copy__(symbol)))

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
//符号别名
__attribute__((alias))
```

# 3、bitwise：

- 表示类型或函数具有特定的位操作行为，当在类型或函数声明中使用性时，编译器将位操作进行更严格的检查；

- 如将使用bitwise标记的类型的变量，与其他未标记类型的变量进行位操作时，编译器将产生警告或错误，指出可能的问题；

```c
typedef unsigned int __attribute__((bitwise)) op_t;
```

