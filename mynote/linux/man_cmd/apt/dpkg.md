# 1、常用命令：

```bash
dpkg -L xxx                           # 列出deb包安装的内容
dpkg -i xxx.deb                       # 安装deb包
dpkg-query -S xxx                     # 查询命令所属的包
dpkg -X package.deb extract           # 解压deb包中内容到extract目录
dpkg -e package.deb extract/DEBIAN    # 解压deb包中的control信息到extract/DEBIAN目录
dpkg-deb -b extract package.deb       # 将extrace目录打包成deb包

# 卸载deb包
dpkg -l | grep xxx                    # 列出deb包，获取deb名称
sudo dpkg -r xxx                      # 卸载deb包
sudo dpkg -P xxx                      # 卸载deb包，并删除配置文件
```
