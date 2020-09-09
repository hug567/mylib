## 1、初始化设置

- **离线安装插件：**
  ```c
  Extensions (Ctrl+Shift+X) -> 从VSIX安装
  ```

- **设置中文：**
  ```c
  Ctrl+Shift+P -> Configure Display Language -> Install additioal languages
  Chinese (Simplified) Language -> Install
  Ctrl+Shift+P -> zh-ch -> Restart
  ```

- **使用bash：**
  ```c
  /* 安装git bash -> 将安装路径添加至系统变量PATH */
  bash --version                                       //在cmd中验证设置是否成功
  /* 在vscode的任意shell中执行：bash */
  ```

- **常用插件：**
  ```c
  c/c++
  code runer
  vim
  ```
## 2、编译调试：

- **编译调试C语言**
  ```c
  调试 -> 添加配置 -> C++(GDB/LLDB)
       -> gcc.exe build and debug active file          //添加launch.json
  /* 修改miDebuggerPath为： */
  "miDebuggerPath": "F:\\Program Files\\mingw64\\bin\\gdb.exe",
  ```
  launch.json
  ```c
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
  task.json
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

## 3、常用快捷键：
```c
Ctrl + Enter                    //在光标下一行插入新行
Shift + Alt + Up                //复制当前行至光标上一行
Shift + Alt + Down              //复制当前行至光标下一行
Ctrl + C                        //不选中时，复制当前行
Ctrl + V                        //粘贴至光标上一行
Ctrl + Up                       //视图上移
Ctrl + Down                     //视图下移
Ctrl + L                        //选中当前行

/* 自定义快捷键 */
Ctrl + Alt + [                  //聚焦至编辑器 (View: Focus First Editor Group)
Ctrl + Alt + ]                  //聚焦至终端 (workbenck.panel.terminal.focus)
```
