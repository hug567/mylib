# 1、常用命令：

```bash
sudo apt install sshpass

sshpass
	-h                                    # 查看帮助
```

# 2、常见用法：

```bash
# sshpass免输入密码登录：
sshpass -p 'R123456' ssh rhosoon@192.168.99.143
# sshpass通过跳板机登录内部机器：
sshpass -p 'hx2023' ssh hx@172.22.195.55 -p 22 -o "ProxyCommand sshpass -p 'R123456' ssh rhosoon@192.168.99.143 -p 22 -W %h:%p"
```

