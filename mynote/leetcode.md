### 1、二维数组转换：
```c

void func(int **_arr)
{
    /* 本地调试： */
    int (*arr)[size] = (int (*)[size])_arr;

    /* leetcode： */
    int **arr = _arr;
}
```