# 1、docker对挂载的主机目录没有需改权限：

- 当前用户的UID/GID与启动的docker容器中用户的UID/GID相同时，docker中可直接修改挂载的属于当前用户的目录和文件；

```bash
# 可修改host用户UID/GID，或docker容器中用户的UID/GID，以修改host当前用户的UID和GID为例：
# 修改用户UID
sudo usermod -u 1000 jenkins
# 修改用户组GID
sudo groupmod -g 1001 jenkins
# 查看用户的UID/GID
id jenkins
```

