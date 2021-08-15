/*
 * 驱动公共头文件
 * 2020-11-13
 */

#include <linux/fs.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/printk.h>

#define log_info(fmt, ...)  printk("[INFO ][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) printk("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define min(a, b) \
{ \
	typeof(a) __a = a; \
	typeof(b) __b = b; \
	return __a < __b ? __a : __b;\
}
