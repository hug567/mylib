# C语言函数指针

 

## 1、函数指针作为结构体参数：

```c
struct math {
    int (*add)(int a, in b);
};
```



## 2、typedef定义函数指针类型：

``` c
typedef int (*func_t)(int a, int b);

struct math {
    func_t add;
}
```



## 3、函数指针作为函数参数

```c
void sort(int *arr, int size, int (*comp)(int a, int b));
void sort(int *arr, int size, func_t comp);    
```

