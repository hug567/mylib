# 1、struct dentry：

```c
struct dentry {
	//name长度小于DNAME_INLINE_LEN时，d_name->name指向d_iname，超过时指向alloc的内存区域
	struct qstr d_name;
	unsigned char d_iname[DNAME_INLINE_LEN];
    //父目录项	
    struct dentry *d_parent;
    //dentry对应的inode
    struct inode *d_inode;
    //dentry对于的超级块
    struct super_block *d_sb;
};
```

