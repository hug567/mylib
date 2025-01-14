# 1、创建用户：

```bash
# 创建数据库文件
filebrowser config init

# 创建管理员用户，有管理员权限
filebrowser users add admin ddf3#jusQR^Z3CTC
# 设置用户scope
filebrowser users update admin --scope /home/hx/filebrowser
# 为用户添加admin权限
filebrowser users update admin --perm.admin

# 创建普通用户
filebrowser users add hx hx123456
# 设置用户scope
filebrowser users update hx --scope /home/hx/filebrowser
# 允许普通用户下载文件
filebrowser users update hx --perm.download
# 禁止普通用户以下权限
filebrowser users update hx --perm.create=false
filebrowser users update hx --perm.rename=false
filebrowser users update hx --perm.delete=false
filebrowser users update hx --perm.share=false
filebrowser users update hx --perm.execute=false
# 禁止普通用户修改密码
filebrowser users update hx --lockPassword=true

# 查看用户
filebrowser users ls

# 删除用户
filebrowser users rm <user>
```

# 2、json配置文件：

```bash
{
        "port" : 53000,
        "address" : "0.0.0.0",
        "log" : "/var/log/filebrowser.log",
        "root" : "/home/hx/filebrowser",
        "database" : "/home/hx/tools/linux-amd64-filebrowser/filebrowser.db",
        "signup" : false,
        "lockPassword" : true,
        "locale" : "zh-cn",
        "singleClick" : true,
        "dateFormat" : true,
        "branding" : {
                "name": "hx",
                "filesPerPage": 50,
                "theme" : "light"
        },
        "__end" : ""
}
```

# 3、启动filebrowser：

## 1）、手动启动：

```bash
filebrowser -c ./config.json -d ./filebrowser.db
```

## 2）、systemd中开机自启动：

- 创建启动脚本：

```bash
# 创建启动脚本，systemd不能直接执行二进制，需在脚本中执行：
vim systemd_filebrowser.sh
#----------------------------------------------#
cd /home/hx/tools/filebrowser
./filebrowser -c ./config.json
#----------------------------------------------#
```

- 创建自启动服务：

```bash
# 创建自定义任务文件：
touch filebrowser.service
# 编辑任务内容：
vim filebrowser.service
#----------------------------------------------#
[Unit]
Description=filebrowser
After=network.target

[Service]
User=hx
ExecStart=/bin/bash /home/hx/tools/filebrowser/systemd_filebrowser.sh
Restart=no

[Install]
WantedBy=multi-user.target
#----------------------------------------------#
# 复制到系统任务目录：
sudo cp filebrowser.service /lib/systemd/system
# 设置开机自启动：
sudo systemctl enable filebrowser
# 启动任务：
sudo systemctl start filebrowser

# 查看启动日志：
journalctl -u filebrowser
# 查看启动进程：
ps aux | grep filebrowser
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

