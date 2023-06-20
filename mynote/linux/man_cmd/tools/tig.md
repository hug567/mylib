# 1、安装：

```bash
sudo apt install tig
```

# 2、常见用法：

```bash
tig [branch]                   # 进入tig模式
j/k                            # 上下切换选择行
	Enter                          # 分屏查看commit详情
	l+q                            # 全屏查看commit详情
↑/↓                            # 上下键选择commit
r                              # 查看所有分支
m                              # 回到主页面
/                              # 搜索内容
```

# 3、配置文件：

```bash
# 配置文件位置： ~/.tigrc
# tig version: 2.4.1

# 颜色设置语法：color area fgcolor bgcolor [attributes]
# 中间分隔线颜色
color title-blur blue default
# 底部聚焦栏颜色 (237:灰)
color title-focus blue 237
# 当前行颜色 (15:白, 239:灰)
color cursor 15 239

# 竖直分割窗口
set vertical-split = true
# 右侧窗口比例
set split-view-width = 70%
```

