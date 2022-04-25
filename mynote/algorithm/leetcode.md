## 1、二维数组转换：

```c
void func(int **array, int row, int col)
{
    /* 本地调试： */
    int (*arr)[col] = (int (*)[col])array;

    /* leetcode： */
    int **arr = array;
    
    //访问
    arr[i][j]
}

/************************************************************************/
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

## 2、获取二维数组大小：

```c
int row = sizeof(arr) / sizeof(arr[0]);            //arr[row][col]
int col = sizeof(arr[0]) / sizeof(arr[0][0]);      //arr[row][col]
```

## 3、注意事项：

```c
1、leetcode中全局变量需在每次运行测试用例时初始化，不能只在定义全局变量时初始化一次；

2、判断字符串为空用：strlen(str) == 0, 不能用 str == NULL；

3、为避免溢出，大写字母转小写字母：ch = ch - 'A' + 'a'，
            小写字母转大写字母：ch = ch - 'a' + 'A';

4、定义字符串，用数组：char str[] = "abc"，不能用 char *str = "abc"，字符串常量不可修改；
```

## 4、交换两个值：

```c
//异或
a = a ^ b
b = a ^ b
a = a ^ b

//加减
a = a + b
b = a - b
a = a - b

```

## 5、需掌握：

```c
qsort;
二维数组指针转换;
创建二维数组;
创建二叉树;
二叉树dfs, bfs;
二维数组bfs;
双指针;
有序数组二分查找;
堆：第k大的元素;
```

