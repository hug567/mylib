# 1、WSL运行docker：

- 安装wsl2：启动或关闭Windows功能 -> 适用于Linux的Windows子系统 -> 虚拟机平台

```bash
# 查看当前安全的linux发行版
wsl -l -v
# 关闭运行的linux(关闭虚拟机进程Vmmem)
wsl --shutdown
# 设置wsl2运行linux发行版
wsl --set-version Ubuntu-22.04 2
```

