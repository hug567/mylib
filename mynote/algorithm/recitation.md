## 1、需背诵的代码：

```shell
1、qsort使用；
2、leetcode 二维数组；
3、创建二叉树；
4、二叉树的：前序、中序、后序、层次遍历，深度；
5、二叉树的DFS、BFS；
6、二叉查找树/二叉搜索树；
7、二维数组(图)的DFS、BFS；
8、二分查找；
```



* 二分查找：

```c
int BinartSearch(int *arr, int size, int target)
{
    int left = 0;
    int right = size - 1;
    int mid;
    
    whle (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}
```

  