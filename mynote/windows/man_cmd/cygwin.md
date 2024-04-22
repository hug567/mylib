# windows中使用cygwin：

## 1、安装cygwin：

- https://www.cygwin.com/install.html
- 下一步 -> 从互联网安装 -> 下一页 -> 根目录 -> 下一页 -> 本地软件包目录 -> 下一页 -> 使用系统代理设置 -> 下一页 -> 用户站点 -> 下一页 -> 视图：完整 -> 搜索：xxx
- 选择手动安装的包：wget、expect、tcl、sshpass、openssh、vim
- -> 下一页 -> 下一页 -> 完成
- 若忘记安装，可再执行cygwin安装程序，新增安装想要安装的程序；

## 2、启动cygwin：

```bash
sshpass -V
expect -v
```

