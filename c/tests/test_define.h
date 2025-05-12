/*
 * 宏定义相关
 * Create: 2025-05-12 11:17:42
 */

/*
 * define宏定义中可返回值
 */
#define func_return_int() \
({ \
	int ret; \
	ret = 1 + 2; \
	ret; \
})
