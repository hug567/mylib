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
- 软件瘦身，当前软件没有使用到的一些库文件可以删除：

```bash
# 目录：
generic：
iconengines：
networkinformation：
imageformats：图像支持
tls：
translations：翻译文件
# 文件：
iconengines/qsvgicon.dll：SVG相关库
D3Dcompiler_47.dll：
opengl32sw.dll：软件模拟OpenGL
Qt6Network.dll：网络相关
Qt6Svg.dll：SVG相关
```

# 2、打包成单独exe文件：

## 1）、带安装程序的打包工具：

- 使用打包工具，将上述程序和库打包成一个单独的exe文件， 如Inno：https://jrsoftware.org/isdl.php#stable

## 2）、单文件打包工具：

- Enigma Virtual Box：https://enigmaprotector.com/en/downloads.html

```bash
选择：主程序文件名称
-> 使用默认：输出虚拟文件名称
-> 添加：添加文件夹递归(X)
-> 打包
```

