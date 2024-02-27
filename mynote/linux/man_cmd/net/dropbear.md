# 1、dropbear免密登录远端：

```bash
# 生成私钥和公钥：
mkdir ~/.ssh
chmod 700 ~/.ssh/
dropbearkey -t rsa -f ~/.ssh/id_dropbear
dropbearkey -y -f ~/.ssh/id_dropbear | grep ssh-rsa > ~/.ssh/id_dropbear.pub
cat ~/.ssh/id_dropbear.pub
# 将id_dropbear.pub中的内容拷贝到远端机器的~/.ssh/authorized_keys
```

