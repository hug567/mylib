## 1、常用cmd命令：

```c
dir                                                      //显示所有文件与目录
D:                                                       //进入D盘
cd <dir>                                                 //进入目录
cls                                                      //清除目录
del <file>                                               //删除文件
```

## 2、cmd自定义字体：

- 推荐字体：Microsoft YaHei Mono，下载后安装即可，之后在cmd中设置字体为Microsoft YaHei Mono；

- cmd：右键 -> 属性 -> 字体 -> Microsoft YaHei Mono；

## 3、cmd设置命令别名(alias)：

- 新建bat脚本文件，如：C:\Users\huangxing\cmdrc.bat，设置命令alias：

```bash
# C:\Users\huangxing\cmdrc.bat
#----------------------------------------------#
@echo off
doskey ls=dir /d $*
#----------------------------------------------#
```

- 修改注册表，让cmd启动时自动执行alias脚本：

  - 进入注册表项：计算机\HKEY_CURRENT_USER\SOFTWARE\Microsoft\Command Processor，若没有Command Processor，需要新建；
  - 在Command Processor中新增字符串值：

  ```bash
  数值名称：AutoRUn
  数值数据：C:\Users\huangxing\cmdrc.bat
  ```

- 再次启动cmd时，将会自动运行自定义的cmdrc.bat文件；

