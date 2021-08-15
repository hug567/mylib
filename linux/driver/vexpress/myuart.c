/*
 * vexpress开发板串口驱动程序
 * 串口类型：pl011
 * qemu重定向串口到pty: -serial pty
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
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include "myuart.h"

#define log_info(fmt, ...)  printk("[INFO ][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) printk("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define DEV_NAME "myuart"

#define UART_DR			0x0  /* Data Register */
#define UART_FR			0x18 /* Flag Register */
#define UART_FR_TXFE		0x80 /* Transmit Fifo Empty */
#define UART_FR_TXFF		0x20 /* Transmit Fifo Full */
#define UART_LCR_H		0x2C
#define UART_CR			0x30 /* Control Register */
#define UART_CR_UARTEN		0x01 /* UART Enable */
#define UART_IMSC		0x38 /* Interrupt Mask Set/Clear Register */
#define UART_IMSC_RXIM		0x10 /* Receive Interrupt Mask */
#define UART_RIS		0x3C /* 原始中断状态寄存器 */
#define UART_RIS_RXRIS		0x10 /* 接收中断状态 */
#define UART_MIS		0x40
#define UART_ICR		0x44 /* 中断清除寄存器 */
#define UART_ICR_RXIC		0x10 /* 清除接收中断 */

/*
 * 获取UART1中断号：cat /proc/interrupts
 */
static struct dts_info {
	unsigned int paddr;
	unsigned int size;
	unsigned int irq;
} g_dts_info[] = { /* vexpress uart info */
	{ 0x10009000, 0x1000, 38 },
	{ 0x1000a000, 0x1000, 39 },
	{ 0x1000b000, 0x1000, 40 },
	{ 0x1000c000, 0x1000, 41 },
};

static struct myuart {
	dev_t devno;
	struct cdev cdev;
	struct class *class;
	void *vaddr;
	unsigned int size;
} g_myuart;

static int myuart_sysfs_init(void)
{
	return 0;
}

static int g_idx = 32;
static int g_count = 0;
ssize_t myuart_proc_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	/* ascii visible char: 32 ~ 126, total 95 */
	if (g_idx > 126) {
		/* 第一次返回0后，cat会再读一次，第二次返回0后，cat结束 */
		g_count++;
		if (g_count == 2) {
			g_idx = 32;
			g_count = 0;
		}
		return 0;
	}
	buf[0] = g_idx; //sprintf(buf, fmt, ...)
	g_idx++;
	return 1;
}

#define TMP_BUF_SIZE 10
ssize_t myuart_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	int already_rx = 0;
	char tmp_buf[TMP_BUF_SIZE + 1] = {0};

	while (already_rx < count) {
		int cur_rx = min(count - already_rx, TMP_BUF_SIZE);
		memset(tmp_buf, 0, TMP_BUF_SIZE + 1);
		copy_from_user(tmp_buf, buf + already_rx, cur_rx);
		already_rx += cur_rx;
		printk("%s", tmp_buf);
	}

	return already_rx;
}

static struct file_operations myuart_proc_fops = {
	.read = myuart_proc_read,
	.write = myuart_proc_write,
};

static struct proc_dir_entry *myuart_proc_entry = NULL;
static int myuart_procfs_init(void)
{
	myuart_proc_entry = proc_create("myuart", 0644, NULL, &myuart_proc_fops);
	if (myuart_proc_entry == NULL) {
		log_error("proc_create failed\n");
		return -1;
	}
	log_info("will create: /proc/uart\n");

	return 0;
}

static void myuart_procfs_exit(void)
{
	proc_remove(myuart_proc_entry);
}

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

static void myuart_write_char(struct myuart *myuart, char ch)
{
	void *base_addr = myuart->vaddr;

	wait_until_txfifo_nfull(myuart);
	writel_relaxed(ch, base_addr + UART_DR);
	if (ch == '\r') {
		writel_relaxed('\n', base_addr + UART_DR);
	}
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
		myuart_write_char(myuart, (char)arg);
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

static char myuart_read_char(struct myuart *myuart)
{
	unsigned int reg_dr;
	void *base_addr = g_myuart.vaddr;

	reg_dr = readl(base_addr + UART_DR);
	return (reg_dr & 0xFF);
}

static irqreturn_t myuart_interrupt(int irq, void *ctx)
{
	char ch;
	unsigned int reg_ris;
	unsigned int reg_icr;
	struct myuart *myuart = (struct myuart *)ctx;
	void *base_addr = myuart->vaddr;

	reg_ris = readl(base_addr + UART_RIS);
	reg_icr = readl(base_addr + UART_ICR);
	if (reg_ris & UART_RIS_RXRIS) {
		ch = myuart_read_char(myuart);
		myuart_write_char(myuart, ch);
		reg_icr |= UART_ICR_RXIC; /* 清除接收中断 */
		writel(reg_icr, base_addr + UART_ICR);
	}
	return IRQ_HANDLED;
}

static void myuart_enable_irq(struct myuart *myuart)
{
	unsigned int imsc;
	void *base_addr = myuart->vaddr;

	imsc = readl(base_addr + UART_IMSC);
	imsc |= UART_IMSC_RXIM; /* 使能接收中断 */
	writel(imsc, base_addr + UART_IMSC);
}

static int myuart_info_init(struct myuart *myuart)
{
	int ret;
	struct dts_info *info = &g_dts_info[1];

	myuart->vaddr = ioremap(info->paddr, info->size);
	if (myuart->vaddr == NULL) {
		log_error("ioremap [0x%x:0x%x] failed\n", info->paddr, info->size);
		return -EIO;
	}
	log_info("ioremap [0x%x:0x%x] to [0x%p:0x%x] success\n",
		 info->paddr, info->size, myuart->vaddr, info->size);

	ret = request_irq(info->irq, myuart_interrupt, 0, "myuart", myuart);
	if (ret < 0) {
		log_error("request_irq failed\n");
		iounmap(myuart->vaddr);
		return ret;
	}

	myuart_enable_irq(myuart);

	return 0;
}

static void myuart_info_exit(struct myuart *myuart)
{
	struct dts_info *info = &g_dts_info[1];

	if (myuart != NULL && myuart->vaddr != NULL) {
		iounmap(myuart->vaddr);
	}
	free_irq(info->irq, NULL);
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

	myuart_procfs_init();
	myuart_sysfs_init();

	log_info("finish %s, will crate /dev/%s\n", __func__, DEV_NAME);

	return 0;
}

static void __exit myuart_exit(void)
{
	struct myuart *myuart = &g_myuart;

	log_info("Enter %s\n", __func__);

	myuart_procfs_exit();
	myuart_info_exit(myuart);

	device_destroy(myuart->class, myuart->devno);
	class_destroy(myuart->class);
	cdev_del(&myuart->cdev);
	unregister_chrdev_region(myuart->devno, 1);
}

module_init(myuart_init);
module_exit(myuart_exit);
MODULE_LICENSE("GPL");
