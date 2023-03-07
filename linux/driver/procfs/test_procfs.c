/*
 * 创建procfs文件
 * 2023-03-07
 */
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROCFS_NAME "test_procfs"

#define log_info(fmt, ...) printk("[I][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_err(fmt, ...)  printk("[E][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

static void *test_procfs_seq_start(struct seq_file *seq, loff_t *pos)
{
	if (*pos > 0) {
		return NULL;
	}
	return seq;
}

static void *test_procfs_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	(*pos)++;
	return test_procfs_seq_start(seq, pos);
}

static void test_procfs_seq_stop(struct seq_file *seq, void *v)
{
}

static int test_procfs_seq_show(struct seq_file *seq, void *v)
{
	seq_printf(seq, "cur func: %s, line: %d\n", __func__, __LINE__);
	seq_printf(seq, "cur task: %s, pid: %d\n", current->comm, current->pid);

	return 0;
}

static struct seq_operations test_procfs_seq_ops = {
	.start	= test_procfs_seq_start,
	.next	= test_procfs_seq_next,
	.stop	= test_procfs_seq_stop,
	.show	= test_procfs_seq_show,
};

static int test_procfs_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &test_procfs_seq_ops);
}

static struct proc_ops test_proc_fops = {
	.proc_open	= test_procfs_open,
	.proc_read	= seq_read,
};

static struct proc_dir_entry *test_proc_entry = NULL;
static int test_create_profs(void)
{
	test_proc_entry = proc_create(PROCFS_NAME, 0644, NULL, &test_proc_fops);
	if (test_proc_entry == NULL) {
		log_err("proc_create failed\n");
		return -1;
	}
	log_info("will create: /proc/test_procfs\n");

	return 0;
}

static void test_delete_procfs(void)
{
	proc_remove(test_proc_entry);
}

static int __init test_procfs_init(void)
{
	return test_create_profs();
}

static void __exit test_procfs_exit(void)
{
	test_delete_procfs();
}

module_init(test_procfs_init);
module_exit(test_procfs_exit);
MODULE_LICENSE("GPL");
