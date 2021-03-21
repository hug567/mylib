/*
 * vexpress开发板网口驱动程序头文件
 * 2021-03-17
 */

#define log_info(fmt, ...)  printk("[INFO ][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) printk("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
