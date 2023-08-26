# 1、基本信息：

- 项目源码：https://github.com/kuaifan/dootask

# 2、安装Docker-compose：

```bash

```

# 3、dootask搭建：

- 中文文档：https://github.com/kuaifan/dootask/blob/master/README_CN.md

```bash
# 通过github克隆项目
git clone -b pro --depth=1 https://github.com/kuaifan/dootask.git
# 或者你也可以使用gitee
git clone -b pro --depth=1 https://gitee.com/aipaw/dootask.git
cd dootask
# 安装项目（可自定义端口）
./cmd install
./cmd install --port 9012
# 卸载
./cmd uninstall
# 重置默认管理员密码
./cmd repassword
# 更换端口
./cmd port 2222
# 停止服务
./cmd stop
# 启动服务器
./cmd start
```

# 4、迁移项目

- 在新项目安装好之后按照以下步骤完成项目迁移：

```bash
#1、备份原数据库,在旧的项目下运行命令：
./cmd mysql backup

# 2、将数据库备份文件及public/uploads目录拷贝至新项目：
cp -r xxx yyy

# 3、还原数据库至新项目，在新的项目下运行命令：
./cmd mysql recovery
```

