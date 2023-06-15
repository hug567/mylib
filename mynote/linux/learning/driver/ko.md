# 1、ko加载：

* Linux驱动编译成ko时，module_init、module_exit展开为：
```c
/*
 * typedef int (*initcall_t)(void);
 */
static inline initcall_t __inittest(void)
        __attribute__((__gnu_inline__))
        __attribute__((__unused__))
        __attribute__((__no_instrument_function__))
        __attribute__((__unused__))
{
        return mml_init;
}
int init_module(void) __attribute__((alias("mml_init")));;

/*
 * typedef void (*exitcall_t)(void);
 */
static inline exitcall_t __exittest(void)
        __attribute__((__gnu_inline__))
        __attribute__((__unused__))
        __attribute__((__no_instrument_function__))
        __attribute__((__unused__))
{
        return mml_exit;
}
void cleanup_module(void) __attribute__((alias("mml_exit")));;
```

- insmod指令调用sys_init_module()函数加载ko：
```c
sys_init_module()  //SYSCALL_DEFINE3(init_module, ...
	load_module()
    	apply_relocations()
    		apply_relocate_add()  //arch/arm64/kernel/module.c
    			case R_AARCH64_CALL26:
					xxx
    			case R_AARCH64_ABS64:
					reloc_data()
			    		mm->init = xxx;
						mm->exit = yyy;
		do_init_module()
			do_one_initcall()
    			ret = fn();  //module_init()
```

- rmmode指令调用sys_delete_module()函数卸载ko：

```c
sys_delete_module()  //SYSCALL_DEFINE2(delete_module, ...
    mod->exit();
```