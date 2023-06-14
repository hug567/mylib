# 文件系统：

## 1、基本数据结构：

```c
struct spuer_block;    //超级块
struct inode;          //索引节点
struct file;           //文件
struct dentry;         //目录项
```

## 2、spuer_block：

一个超级块对应一个文件系统，存储文件系统中的所有inode

## 3、inode：

inode分内存中的inode和磁盘中的inode；

一个inode对应磁盘中的一个文件；

## 4、file：

file表示打开的文件描述符，每个打开的文件对应一个file，由内核在打开时创建，；

## 5、dentry：

