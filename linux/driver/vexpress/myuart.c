/*
 * vexpress开发板串口驱动程序
 * 串口类型：pl011
 * 2021-01-05
 */
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "myuart.h"

#define log_info(fmt, ...)  printk("[INFO ][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) printk("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define DEV_NAME "myuart"

#define UART_DR			0x0 /* data register */
#define UART_FR			0x18 /* flag register */
#define UART_FR_TXFE		0x80 /* transmit fifo empty */
#define UART_FR_TXFF		0x20 /* transmit fifo full */
#define UART_LCR_H		0x2C
#define UART_CR			0x30
#define UART_IMSC		0x38
#define UART_RIS		0x3C
#define UART_MIS		0x40
#define UART_ICR		0x44

static struct dts_info {
	unsigned int paddr;
	unsigned int size;
	unsigned int irq;
} g_dts_info[] = {
	{ 0x1000c000, 0x1000, 5 },
	{ 0x1000b000, 0x1000, 6 },
	{ 0x1000d000, 0x1000, 7 },
	{ 0x1000e000, 0x1000, 8 },
};

static struct myuart {
	dev_t devno;
	struct cdev cdev;
	struct class *class;
	void *vaddr;
	unsigned int size;
} g_myuart;

#define print_reg(vaddr, reg) log_info(#reg " = 0x%x\n", readl((vaddr) + (reg)))
static void dfx_print_all_register(struct myuart *myuart)
{
	log_info("vaddr = %p\n", myuart->vaddr);
	print_reg(myuart->vaddr, UART_DR);
	print_reg(myuart->vaddr, UART_FR);
	print_reg(myuart->vaddr, UART_LCR_H);
	print_reg(myuart->vaddr, UART_CR);
	print_reg(myuart->vaddr, UART_IMSC);
	print_reg(myuart->vaddr, UART_RIS);
	print_reg(myuart->vaddr, UART_MIS);
	print_reg(myuart->vaddr, UART_ICR);
}

#define MAX_WAIT_COUNR 1U << 31
int wait_until_txfifo_nfull(struct myuart *myuart)
{
	int count = 0;
	while ((readl(myuart->vaddr + UART_FR) & UART_FR_TXFF) && count < MAX_WAIT_COUNR) {
		count++;
	}
	if (count == MAX_WAIT_COUNR) {
		log_error("wait tx fifo not full timeout\n");
		return -1;
	} else {
		return 0;
	}
}

static int myuart_open(struct inode *inode, struct file *file)
{
	log_info("Enter %s\n", __func__);
	file->private_data = &g_myuart;
	return 0;
}

static int myuart_release(struct inode *inode, struct file *file)
{
	//struct myuart *myuart = (struct myuart *)file->private_data;

	log_info("Enter %s\n", __func__);

	//dfx_print_all_register(myuart);

	return 0;
}

static void write_char(struct myuart *myuart, char ch)
{
	//log_info("ch = %c, vaddr = %p\n", ch, myuart->vaddr);
	wait_until_txfifo_nfull(myuart);
	writel_relaxed(ch, myuart->vaddr + UART_DR);
}

static long myuart_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct myuart *myuart = (struct myuart *)file->private_data;

	//log_info("Enter %s\n", __func__);

	if (myuart == NULL) {
		log_error("myuart is NULL\n");
		return -EINVAL;
	}

	switch (cmd) {
	case CMD_WRITE_CHAR: {
		write_char(myuart, (char)arg);
	}
		break;
	default:
		log_error("unsupport cmd %u\n", cmd);
		break;
	}
	return 0;
}

static struct file_operations g_myuart_fops = {
	.owner			= THIS_MODULE,
	.open			= myuart_open,
	.release		= myuart_release,
	.unlocked_ioctl		= myuart_ioctl,
};

static int myuart_info_init(struct myuart *myuart)
{
	struct dts_info *info = &g_dts_info[0];

	myuart->vaddr = ioremap(info->paddr, info->size);
	if (myuart->vaddr == NULL) {
		log_error("ioremap [0x%x:0x%x] failed\n", info->paddr, info->size);
		return -EIO;
	}
	log_info("ioremap [0x%x:0x%x] to [0x%p:0x%x] success\n",
		 info->paddr, info->size, myuart->vaddr, info->size);
	return 0;
}

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

	ret = myuart_info_init(&g_myuart);
	if (ret < 0) {
		log_error("myuart_info_init failed\n");
		return ret;
	}

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
