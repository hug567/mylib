## 1、CLion常用设置


```c
//显示空格
File -> Settings -> Editor -> General -> Appearance -> Show whitespaces

//设置空格显示颜色
Files -> Settings -> Editor -> Color Scheme -> General -> Text -> Whitespaces
默认：464741
更亮：808080

//设置选择背景色
Files -> Settings -> Editor -> Color Scheme -> General -> Editor -> Selection background
默认：575959
更亮：909090

//设置参考竖线
Files -> Settings -> Editor -> Color Style -> Hard wrap at(80)

//设置窗口背景与编辑窗口颜色一致
对空白的编辑窗口背景截一个图，将次图片作为窗口背景
File -> Setting -> Appearance & Behavior -> Appearance -> UI Options -> Background Images -> Image -> Oppacity(100)

//设置行号颜色
Files -> Settings -> Editor -> Color Scheme -> General -> Code -> Line Number -> Foreground
默认：F8F8F2
更暗：808080

//关闭参数提示
Files -> Settings -> Editor -> Inlay Hints -> C/C++ -> Show parameter hints
```

```c
//修改背景色
Files -> Settings -> Editor -> Color Scheme -> General -> Text -> Default text -> Background
默认：272822
较亮：3C3F41

//控制台背景色
Files -> Settings -> Editor -> Color Scheme -> Console Colors -> Console -> Background
较亮：3C3F41
  
```

## 2、编译已有文件：

```c
New Project -> C Executable -> Location -> Create -> Yes

左侧工程名上右键 -> New -> CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(helloworld C)
set(CMAKE_C_STANDARD 99)
add_executable(helloworld main.c)

左侧文件CMakeLists.txt上右键 -> Load CMake Project

Run -> Run -> 0. Edit Configurations -> Add New Configuration -> CMake Application
    -> Name/Target/Executable (helloworld) -> Apply -> Close

Run -> Run 'helloworld'

```

## 3、加载现有文件到工程：

```c
//方法一：手动更新
修改CMakeLists.txt -> 在CMakeLists.txt上右击 -> Reload CMake Project
    
//方法二：自动更新
File -> Settings -> Build,Execution,Deployment -> CMake -> Automatically reload CMake project on editing
```

## 4、常用调试方法：

```c
//1、debug查看指针一维数组
*(int(*)[5])(arr)
```

