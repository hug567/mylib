# 1、创建用户：

```bash
# 创建数据库文件
filebrowser config init

# 创建管理员用户，有管理员权限
filebrowser users add admin ddf3#jusQR^Z3CTC
# 设置用户scope
filebrowser users update admin --scope /home/rhosoon/filebrowser
# 为用户添加admin权限
filebrowser users update admin --perm.admin

# 创建普通用户
filebrowser users add rhosoon rs123456
# 设置用户scope
filebrowser users update rhosoon --scope /home/rhosoon/filebrowser
# 允许普通用户下载文件
filebrowser users update rhosoon --perm.download
# 禁止普通用户以下权限
filebrowser users update rhosoon --perm.create=false
filebrowser users update rhosoon --perm.rename=false
filebrowser users update rhosoon --perm.delete=false
filebrowser users update rhosoon --perm.share=false
filebrowser users update rhosoon --perm.execute=false
# 禁止普通用户修改密码
filebrowser users update rhosoon --lockPassword=true

# 查看用户
filebrowser users list

# 删除用户
filebrowser users rm <user>
```

# 2、json配置文件：

```bash
{
        "port" : 45000,
        "address" : "0.0.0.0",
        "log" : "/var/log/filebrowser.log",
        "root" : "/home/rhosoon/filebrowser",
        "database" : "/home/rhosoon/tools/linux-amd64-filebrowser/filebrowedr.db",
        "signup" : false,
        "lockPassword" : true,
        "locale" : "zh-cn",
        "singleClick" : true,
        "dateFormat" : true,
        "branding" : {
                "name": "Rhosoon",
                "filesPerPage": 50,
                "theme" : "light"
        },
        "__end" : ""
}
```

# 3、启动filebrowser：

```bash
filebrowser -c ./config.json -d ./filebrowser.db
```

