# 1、发布程序：

- 构建Release版程序，然后进入build目录，将生成的exe文件拷贝到空目录中，如：

```bash
# 生成的Release版文件：
D:\code\QT\zynq-flash\build\Desktop_Qt_6_7_2_MinGW_64_bit-Release\release\zynq-flash.exe
```

- 启动Qt命令行程序：Qt 6.7.2 (MinGW 11.2.0 64-bit)，进入放置生成的exe文件的目录，如：

```bash
# 进入目录：
D: && cd \code\QT\zynq-flash\build\Desktop_Qt_6_7_2_MinGW_64_bit-Release\temp
# 自动获取依赖：
windeployqt zynq-flash.exe
```

- 从QT安装目录中查看缺失的dll文件，拷贝到上述目录，如：

```bash
# QT库目录：
D:\ProgramFiles\QT6\6.7.2\mingw_64\bin
# 复制缺失的文件：
libgcc_s_seh-1.dll
libstdc++-6.dll
libwinpthread-1.dll
```

- 双击exe文件，验证是否能独立运行；

# 2、打包成单独exe文件：

- 使用打包工具，将上述程序和库打包成一个单独的exe文件， 如Inno：https://jrsoftware.org/isdl.php#stable

```bash
```

