# 1、用在file_operations中：

```c
static void *test_seq_start(struct seq_file *m, loff_t *pos)
{
        if (*pos == 0) {
                return m;
        } else {
                return NULL;
        }
}

static void *test_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
        *pos = 1;

        return NULL;
}

static void test_seq_stop(struct seq_file *m, void *v)
{
}

static int test_seq_show(struct seq_file *m, void *v)
{
        seq_printf(m, "Enyer %s\n", __func__);

        return 0;
}

static struct seq_operations sops = {
    .start = test_seq_start,
    .stop = test_seq_stop,
    .next = test_seq_next,
    .show = test_seq_show,
};

static int test_open(struct inode *inode, struct file *file)
{
    return seq_open(file, *sops);
}

static struct file_operations fops = {
    .open = test_open,
    .release = seq_release,
    .read = seq_read,
};
```

