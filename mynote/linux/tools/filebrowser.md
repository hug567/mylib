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

# 4、开启https：

- ssl证书：
  - key：服务器上的私钥文件，用于对发送给客户端数据的加密，以及对从客户端接收到数据的解密
  - csr：证书签名请求文件，用于提交给证书颁发机构（CA）对证书签名
  - crt：由证书颁发机构（CA）签名后的证书，或者是开发者自签名的证书，包含证书持有人的信息，持有人的公钥，以及签署者的签名等信息

```bash
# 安装openssl
sudo apt install openssl
# 生成未加密的私钥文件(key)：
openssl genpkey -algorithm RSA -out filebrowser.key
# 根据私钥文件(key)生成证书签名请求文件(csr)：
openssl req -new -key filebrowser.key -out filebrowser.csr
# 根据私钥文件(key)和证书签名请求文件(csr)生成自签名证书(crt)，有效期3560天：
openssl x509 -req -days 3650 -in filebrowser.csr -signkey filebrowser.key -out filebrowser.crt

# 修改filebrowser配置文件：

# 启动filebrowser：

filebrowser -c ./config.json -d ./filebrowser.db config set --cert filebrowser.crt --key filebrowser.key
```

