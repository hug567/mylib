### 1、二维数组转换：

```c
void func(int **_arr)
{
    /* 本地调试： */
    int (*arr)[COL_SIZE] = (int (*)[COL_SIZE])_arr;

    /* leetcode： */
    int **arr = _arr;
}
```

### 2、获取二维数组大小：

```c
int row = sizeof(arr) / sizeof(arr[0]);
int col = sizeof(arr[0]) / sizeof(arr[0][0]);
```

### 3、注意事项：

```c
1、leetcode中全局变量需在运行代码中初始化；
```