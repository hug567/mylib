/*
 * linux字符设备驱动练习：创建单个字符设备
 * OS: Ubuntu 18.04, linux-4.15.0
 * 2020-07-17
 */
#include "common.h"

#define DEV_NAME "mychar2"

static int mychar2_proc_init(void)
{
	return 0;
}

static void mychar2_proc_exit(void)
{
}

static int mychar2_open(struct inode *inode, struct file *file)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static ssize_t mychar2_read(struct file *file, char __user *buf, size_t count,
			  loff_t *offp)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static ssize_t mychar2_write(struct file *file, const char __user *buf,
			   size_t count, loff_t *offtp)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

long mychar2_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static struct file_operations g_mychar2_fops = {
	.owner		= THIS_MODULE,
	.open		= mychar2_open,
	.read		= mychar2_read,
	.write		= mychar2_write,
	.unlocked_ioctl	= mychar2_ioctl,
};

static dev_t mychar2_devno = 0;
static struct cdev mychar2_dev;
static struct class *g_class = NULL;
static int __init mychar2_init(void)
{
	int ret;

	log_info("Enter %s\n", __func__);

	ret = mychar2_proc_init();
	if (ret < 0) {
		log_error("proc init failed\n");
		return ret;
	}

	ret = alloc_chrdev_region(&mychar2_devno, 0, 1, DEV_NAME);
	if (ret < 0) {
		log_info(KERN_ERR "alloc chrdev region failed\n");
		mychar2_proc_exit();
		return ret;
	}
	log_info("alloc devno major = %d, minor = %d\n",
		 MAJOR(mychar2_devno), MINOR(mychar2_devno));

	cdev_init(&mychar2_dev, &g_mychar2_fops);

	ret = cdev_add(&mychar2_dev, mychar2_devno, 1);
	if (ret < 0) {
		log_error("cdev add failed\n");
		mychar2_proc_exit();
		unregister_chrdev_region(mychar2_devno, 1);
		return ret;
	}

	g_class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(g_class)) {
		log_error("class create failed\n");
		mychar2_proc_exit();
		unregister_chrdev_region(mychar2_devno, 1);
		return PTR_ERR(g_class);
	}

	device_create(g_class, NULL, mychar2_devno, NULL, DEV_NAME);

	log_info("finish %s, will crate char dev %s\n", __func__, DEV_NAME);

	return 0;
}

static void __exit mychar2_exit(void)
{
	log_info("Enter %s\n", __func__);

	mychar2_proc_exit();
	device_destroy(g_class, mychar2_devno);
	class_destroy(g_class);
	cdev_del(&mychar2_dev);
	unregister_chrdev_region(mychar2_devno, 1);
}

module_init(mychar2_init);
module_exit(mychar2_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huang Xing");
