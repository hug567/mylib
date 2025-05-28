# 1、常用方法：

### 1）、在编译时计算结构体大小：

```bash
# 任意选择选择一个c文件，在文件中加入#error，则编译到该文件时，会报错停止，此时可获取到编译该文件的完整gcc命令：
#error xxx

# 在上述c文件中添加使用sizeof计算结构体大小，同时删除上述添加的#error：
printf("[hx-debug] sizeof(struct sockaddr_in) = %d\n", sizeof(struct sockaddr_in));

# 编译时添加gcc参数：-fdump-tree-original，会生成*.original结尾的文件，其中将sizeof()计算为了实际值：
gcc -fdump-tree-original test.c

# test.c.original中计算后的内容：
printf ((const char * restrict) "[hx-debug] sizeof(struct sockaddr_in) = %d\n", 16);
```

