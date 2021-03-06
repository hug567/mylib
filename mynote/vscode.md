## 1、初始化设置

#### 1)、 离线安装插件：
```c
Extensions (Ctrl+Shift+X) -> 从VSIX安装
```

#### 2）、 设置中文：

```c
Ctrl+Shift+P -> Configure Display Language -> Install additioallanguages
Chinese (Simplified) Language -> Install
Ctrl+Shift+P -> zh-ch -> Restart
```


#### 3）、 使用bash：
```c
/* 安装git bash -> 将安装路径添加至系统变量PATH */
bash --version                                       //在cmd中验证设置否成功
/* 在vscode的任意shell中执行：bash */
```

#### 4）、 常用插件：

```c
c/c++
code runer
vim
remote-ssh
clang-format
```

#### 5）、设置竖直参考线：

```c
Ctrl + Shift + P -> Open Settings

"editor.rulers": [120], /* 列宽竖线 */

```

#### 6）、保存时删除行尾空格：

```c
Ctrl + Shift + P -> Preferences: Open Settings (UI)
                 -> 选中Files: Trim Trailing Whitespace
/* 或： */
Ctrl + Shift + P -> Preferences: Open Settings (JSON)
                 -> 添加："files.trimTrailingWhitespace": true,
```

## 2、编译调试C语言：

```c
task.json                                  //编译配置文件
launch.json                                //调试配置文件
```

#### 1）、自动创建launch.json和task.json：

```c
运行(C) -> 添加配置 -> C++(GDB/LLDB) -> gcc.exe build and debug active file
```

#### 2）、配置launch.json：

```c
/* 修改miDebuggerPath为： */
"miDebuggerPath": "F:\\Program Files\\mingw64\\bin\\gdb.exe",
/**********************************************************************/
{
  // 使用 IntelliSense 了解相关属性。
  // 悬停以查看现有属性的描述。
  // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
  "version": "0.2.0",
  "configurations": [
      {
          "name": "gcc.exe build and debug active file",
          "type": "cppdbg",
          "request": "launch",
          "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
          "args": [],
          "stopAtEntry": false,
          "cwd": "${workspaceFolder}",
          "environment": [],
          "externalConsole": false,
          "MIMode": "gdb",
          "miDebuggerPath": "F:\\Program Files\\mingw64\\bin\\gdb.exe",
          "setupCommands": [
              {
                  "description": "为 gdb 启用整齐打印",
                  "text": "-enable-pretty-printing",
                  "ignoreFailures": true
              }
          ],
          "preLaunchTask": "gcc.exe build active file"
      }
  ]
}
```

#### 3）、配置task.json：

```c
{
  "tasks": [
      {
          "type": "shell",
          "label": "gcc.exe build active file",
          "command": "F:\\Program Files\\mingw64\\bin\\gcc.exe",
          "args": [
              "-g",
              "${file}",
              "-o",
              "${fileDirname}\\${fileBasenameNoExtension}.exe"
          ],
          "options": {
              "cwd": "F:\\Program Files\\mingw64\\bin"
          },
          "problemMatcher": [
              "$gcc"
          ],
          "group": "build"
      }
  ],
}
```

#### 4）、创建c_cpp_properties.json：
```c
待补充
```

## 3、常用操作：
```c
Ctrl + Enter                    //在光标下一行插入新行
Shift + Alt + Up                //复制当前行至光标上一行
Shift + Alt + Down              //复制当前行至光标下一行
Ctrl + C                        //不选中时，复制当前行
Ctrl + V                        //粘贴至光标上一行
Ctrl + Up                       //视图上移
Ctrl + Down                     //视图下移
Ctrl + L                        //选中当前行
Shift + Alt + 鼠标左键           //按列选中
Ctrl + F4                       //关闭编辑器窗口

/* 自定义快捷键： */
Ctrl + Shift + p -> Preferences: Open Keyboard Shortcuts
Ctrl + Alt + [                  //聚焦至编辑器 (View: Focus First Editor Group)
Ctrl + Alt + ]                  //聚焦至终端 (terminal.focus)
```

## 4、vscode连接linux主机：

vscode安装插件：remote-ssh

windows免密码登录linux主机，在cmd中执行：

```c
ssh-keygen -t rsa
```

复制文件中C:\Users\Administrator\.ssh\id_rsa.pub的内容在linux机器中的 ~/.ssh/authorized_keys 文件中。

## 5、常用代码风格设置：

#### 1）、设置tab：

```c
使用空格缩进：Ctrl+Shift+p -> Indent Using Spaces -> 4
使用tab缩进：Ctrl+Shift+p -> Indent Using Tabs -> 4
```

#### 2）、设置空格、tab颜色：

```c
F:\Program Files\Microsoft VS Code\resources\app\extensions\theme-monokai\themes\monokai-color-theme.json
"editorWhitespace.foreground":"#464741",          //#808080（灰色）
```

## 6、格式化代码：

```c
待补充
```