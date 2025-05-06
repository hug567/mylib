# 1、发布位单文件：

- visual studio 2022：

```bash
解决方案资源管理器 -> 在解决方案上右键 -> 发布(B)... -> 显示所有设置
	配置：Release | Any CPU
	目标框架：net8.0-windows
	部署模式：独立
	目标运行时：win-x86
	目标位置：...
	文件发布选项：
		[勾选]生成单个文件
保存 -> 发布
```

- 国内NuGet源：

```bash
https://nuget.cdn.azure.cn/v3/index.json

https://repo.huaweicloud.com/repository/nuget/v3/index.json
```

