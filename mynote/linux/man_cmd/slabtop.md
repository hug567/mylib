# 1、常用命令：

```bash
slabtop                   # 显示内核对象
slabtop -d 1              # 更新间隔(s)
slabtop -s <char>         # 按指定顺序排序
  a                         # 按活动对象数排序
  b                         # 按每slab对象数排序
  c                         # 按cache大小排序
  l                         # 按slab数排序
  v                         # 按活动slab数排序
  n                         # 按名称排序
  o                         # 按对象数排序 (默认选项)
  p                         # 按每slag页数排序
  s                         # 按对象大小排序
  u                         # 按cache使用率排序
```
