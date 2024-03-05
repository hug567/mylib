# 1、常用快捷键：

```bash
Ctrl+Page Up                    # 进入前一个页面
Ctrl+Page Down                  # 进入后一个页面
Ctrl+T                          # 新建页面
Ctrl+W                          # 关闭当前页面
```

# 2、常见问题：

## 1)、访问局域网https报错ERR_SSL_KEY_USAGE_INCOMPATIBLE：

- 创建注册表项：

```bash
# Chrome:
计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Google\Chrome
RSAKeyUsageForLocalAnchorsEnabled            REG_DWORD            0x00000000 (0)

# Edge:
计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Edge
```

- 浏览器中确认Policy: [chrome://policy/](chrome://policy/)

