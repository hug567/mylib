/*
 * Learn linux char driver
 * OS: Ubuntu 18.04, linux-4.15.0
 * 2020-07-17
 */
#include "common.h"

#define DEV_NAME "test_char2"

static int tchar_open(struct inode *inode, struct file *file)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static ssize_t tchar_read(struct file *file, char __user *buf, size_t count,
			  loff_t *offp)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static ssize_t tchar_write(struct file *file, const char __user *buf,
			   size_t count, loff_t *offtp)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

long tchar_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	log_info("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static struct file_operations g_tchar_fops = {
	.owner		= THIS_MODULE,
	.open		= tchar_open,
	.read		= tchar_read,
	.write		= tchar_write,
	.unlocked_ioctl	= tchar_ioctl,
};

static dev_t tchar2_devno = 0;
static struct cdev tchar2_dev;
static int __init test_char_init(void)
{
	int ret;

	log_info("Enter %s\n", __func__);
	ret = alloc_chrdev_region(&tchar2_devno, 0, 1, DEV_NAME);
	if (ret < 0) {
		log_info(KERN_ERR "alloc chrdev region failed\n");
		return ret;
	}
	log_info("alloc devno major = %d, minor = %d\n",
		 MAJOR(tchar2_devno), MINOR(tchar2_devno));

	cdev_init(&tchar2_dev, &g_tchar_fops);

	ret = cdev_add(&tchar2_dev, tchar2_devno, 1);
	if (ret < 0) {
		log_info("cdev add failed\n");
		unregister_chrdev_region(tchar2_devno, 1);
		return ret;
	}
	log_info("finish %s, will crate char dev %s\n", __func__, DEV_NAME);

	return 0;
}

static void __exit test_char_exit(void)
{
	log_info("Enter %s\n", __func__);
	cdev_del(&tchar2_dev);
	unregister_chrdev_region(tchar2_devno, 1);
}

module_init(test_char_init);
module_exit(test_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huang Xing");
