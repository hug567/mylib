/*
 * Learn linux char driver
 * OS: Ubuntu 18.04, linux-4.15.0
 * 2020-07-17
 */

#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/printk.h>

static int g_tchar_major = 0;
static struct class *g_tchar_class = NULL;

static int tchar_open(struct inode *inode, struct file *file)
{
	printk("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

int tchar_release(struct inode *inode, struct file *file)
{
	printk("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static ssize_t tchar_read(struct file *file, char __user *buf, size_t count,
			  loff_t *offp)
{
	printk("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static ssize_t tchar_write(struct file *file, const char __user *buf,
			   size_t count, loff_t *offtp)
{
	printk("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return count;
}

long tchar_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk("[%s:%d] Enter %s success\n", __func__, __LINE__, __func__);
	return 0;
}

static struct file_operations g_tchar_fops = {
	.owner		= THIS_MODULE,
	.open		= tchar_open,
	.release	= tchar_release,
	.read		= tchar_read,
	.write		= tchar_write,
	.unlocked_ioctl	= tchar_ioctl,
};

static int __init test_char_init(void)
{
	printk(KERN_INFO "Enter %s success\n", __func__);

	/* devno为0将动态申请 */
	g_tchar_major = register_chrdev(0, "test_char", &g_tchar_fops);
	if (g_tchar_major < 0) {
		printk(KERN_ERR "register chrdev failed\n");
		return -ENODEV;
	}
	printk(KERN_INFO "alloc test_char major = %d\n", g_tchar_major);

	g_tchar_class = class_create(THIS_MODULE, "test_char");
	if (IS_ERR(g_tchar_class)) {
		printk(KERN_ERR "class create failed\n");
		unregister_chrdev(g_tchar_major, "test_char");
		return PTR_ERR(g_tchar_class);
	}

	device_create(g_tchar_class, NULL, MKDEV(g_tchar_major, 0),
		      NULL, "test_char");

	printk(KERN_INFO "create char device /dev/test_char success\n");

	return 0;
}

static void __exit test_char_exit(void)
{
	printk(KERN_INFO "Enter %s success\n", __func__);

	device_destroy(g_tchar_class, MKDEV(g_tchar_major, 0));
	class_destroy(g_tchar_class);
	unregister_chrdev(g_tchar_major, "test_char");
}

module_init(test_char_init);
module_exit(test_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huang Xing");
