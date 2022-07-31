/*
 * linux test driver
 * 2022-07-19
 */
#include <linux/module.h>

static int __init linux_driver_init(void)
{
	return 0;
}

static void __exit linux_driver_exit(void)
{
}

module_init(linux_driver_init);
module_exit(linux_driver_exit);
