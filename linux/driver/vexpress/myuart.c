/*
 * vexpress开发板串口驱动程序
 * 串口类型：pl011
 * 2021-01-05
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

#define DEV_NAME "myuart"

static struct myuart {
	dev_t devno;
	struct cdev cdev;
	struct class *class;
} g_myuart;

static int myuart_open(struct inode *inode, struct file *file)
{
	log_info("Enter %s\n", __func__);
	return 0;
}

static int myuart_release(struct inode *inode, struct file *file)
{
	log_info("Enter %s\n", __func__);
	return 0;
}

static long myuart_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	log_info("Enter %s\n", __func__);
	return 0;
}

static struct file_operations g_myuart_fops = {
	.owner			= THIS_MODULE,
	.open			= myuart_open,
	.release		= myuart_release,
	.unlocked_ioctl		= myuart_ioctl,
};

static int __init myuart_init(void)
{
	int ret;
	struct myuart *myuart = &g_myuart;

	log_info("Enter %s\n", __func__);

	ret = alloc_chrdev_region(&myuart->devno, 0, 1, DEV_NAME);
	if (ret < 0) {
		log_error("alloc chrdev region failed\n");
		return ret;
	}
	log_info("alloc devno major = %d, minor = %d\n",
		 MAJOR(myuart->devno), MINOR(myuart->devno));

	cdev_init(&myuart->cdev, &g_myuart_fops);

	ret = cdev_add(&myuart->cdev, myuart->devno, 1);
	if (ret < 0) {
		log_error("cdev add failed\n");
		unregister_chrdev_region(myuart->devno, 1);
		return ret;
	}

	myuart->class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(myuart->class)) {
		log_error("class create failed\n");
		unregister_chrdev_region(myuart->devno, 1);
		cdev_del(&myuart->cdev);
		return PTR_ERR(myuart->class);
	}

	device_create(myuart->class, NULL, myuart->devno, NULL, DEV_NAME);

	log_info("finish %s, will crate /dev/%s\n", __func__, DEV_NAME);

	return 0;
}

static void __exit myuart_exit(void)
{
	struct myuart *myuart = &g_myuart;

	log_info("Enter %s\n", __func__);

	device_destroy(myuart->class, myuart->devno);
	class_destroy(myuart->class);
	cdev_del(&myuart->cdev);
	unregister_chrdev_region(myuart->devno, 1);
}

module_init(myuart_init);
module_exit(myuart_exit);
MODULE_LICENSE("GPL");
