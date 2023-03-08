# 1、系统调用路径：

```c
el0_sync  //arch/arm64/kernel/entry.S
	el0_sync_handler  //arch/arm64/kernel/entry-common.c
		el0_svc
			do_el0_svc  //arch/arm64/kernel/syscall.c
				el0_svc_common
    				invoke_syscall
						syscall_table

//系统调用返回
ret_to_user  //arch/arm64/kernel/entry.S
    work_pending
```

