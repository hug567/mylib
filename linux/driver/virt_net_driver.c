/*
 * Practice: Virtual netwotk card device driver
 * Qemu: qemu-system-arm 4.0.1
 * Board: qemu virt-4.0
 * Linux: linux-4.15.0
 * Date: 2020-09-19
 */
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/printk.h>

#define vnet_log(fmt, ...) printk("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

static struct net_device *g_vnet_dev = NULL;


static int vnet_open(struct net_device *dev)
{
	vnet_log("Enter %s success\n", __func__);
	return 0;
}

static int vnet_stop(struct net_device *dev)
{
	vnet_log("Enter %s success\n", __func__);
	return 0;
}

static netdev_tx_t vnet_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	vnet_log("Enter %s success\n", __func__);
	return NETDEV_TX_OK;
}

static struct net_device_ops g_vnet_ops = {
	.ndo_open = vnet_open,
	.ndo_stop = vnet_stop,
	.ndo_start_xmit = vnet_start_xmit,
};

static int vnet_init(void)
{
	int ret;

	vnet_log("Enter %s success\n", __func__);
	g_vnet_dev= alloc_netdev(0, "eth%d", NET_NAME_UNKNOWN, ether_setup);
	if (g_vnet_dev == NULL) {
		printk("alloc netdev failed\n");
		return -1;
	}

	g_vnet_dev->netdev_ops = &g_vnet_ops;
	/* 初始化MAC地址 */
	g_vnet_dev->dev_addr[0] = 0x08;
	g_vnet_dev->dev_addr[1] = 0x89;
	g_vnet_dev->dev_addr[2] = 0x89;
	g_vnet_dev->dev_addr[3] = 0x89;
	g_vnet_dev->dev_addr[4] = 0x89;
	g_vnet_dev->dev_addr[5] = 0x89;

	ret = register_netdev(g_vnet_dev);
	if (ret < 0) {
		printk("register netdev failed\n");
		return ret;
	}

	return 0;
}

static void vnet_exit(void)
{
	vnet_log("Enter %s success\n", __func__);
	unregister_netdev(g_vnet_dev);
	free_netdev(g_vnet_dev);
}

module_init(vnet_init);
module_exit(vnet_exit);
