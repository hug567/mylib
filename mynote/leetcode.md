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
int row = sizeof(arr) / sizeof(arr[0]);            //arr[row][col]
int col = sizeof(arr[0]) / sizeof(arr[0][0]);      //arr[row][col]
```

### 3、注意事项：

```c
1、leetcode中全局变量需在每次运行测试用例时初始化；
```

### 4、二维数组：

```c
a[2][3]:
    a              //类型: int (*)[3]
    a[0]           //类型: int *
    a[0][0]        //类型: int
    &a[0]          //类型: int (*)[3], &a[0] = a
    &a[0][0]       //类型: int *, &a[0][0] = a[0]

void print_array(int **array, int row, int col)
{
    int i, j;
    int *arr1 = (int *)array;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d", *(arr1 + i * col + j)); //arr1[i][j]
        }
    }
    
    int (*arr2)[col] = (int (*)[col])array;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d", arr2[i][j]); //arr2[i][j]
        }
    }
}
```

