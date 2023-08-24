#include <linux/module.h>
#include <linux/printk.h>

#define log_info(fmt, ...) \
	printk("[hx-debug][I][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

static int test_create_ko_init(void)
{
	log_info("Enter %s\n", __func__);
	return 0;
}

static void test_create_ko_exit(void)
{
	log_info("Enter %s\n", __func__);
}

module_init(test_create_ko_init);
module_exit(test_create_ko_exit);
