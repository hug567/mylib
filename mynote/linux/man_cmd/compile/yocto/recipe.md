# 1、任务常用设置：

```bash
# 不执行某个任务
do_rm_work[noexec] = "1"

# 强制每次均执行某个任务
do_configure[nostap] = "1"

# 在recipe的各任务间插入自定义任务，如：
addtask my_deploy after do_install
addtask my_install before do_install after do_compile
```

