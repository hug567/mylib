# 1、常用方法：

### 1）、在编译时计算结构体大小：

```bash
# 在c语言中使用sizeof计算结构体大小：
printf("[hx-debug] sizeof(struct sockaddr_in) = %d\n", sizeof(struct sockaddr_in));

# 编译时添加gcc参数：-fdump-tree-original，会生成*.original结尾的文件，其中将sizeof()计算为了实际值：
gcc -fdump-tree-original test.c

# test.c.original中计算后的内容：
printf ((const char * restrict) "[hx-debug] sizeof(struct sockaddr_in) = %d\n", 16);
```

