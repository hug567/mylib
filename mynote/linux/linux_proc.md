## 1、创建proc文件：
```c
/*
 * 创建proc文件：linux/proc_fs.h
 *   输入：
 *     name: 文件名
 *     mode: 模式，类似文件权限，如：0644
 *     parent: 父入口， NULL表示：/proc
 *     proc_fops: 文件操作接口
 *   输出：
 *     struct proc_dir_entry *: 
 */
struct proc_dir_entry *proc_create(const char *name, umode_t mode, struct proc_dir_entry *parent, const struct file_operations *proc_fops);

/*
 * 删除proc文件：linux/proc_fs.h
 *   name: 文件名
 *   parent: 父入口， NULL表示：/proc
 */
void remove_proc_entry(const char *name, struct proc_dir_entry *parent)

/* 常用fops: linux/fs.h */
struct file_operations {
    ...
    ssize_t (*read)(struct file *file, char __user *buf, size_t count, loff_t *data);
    ssize_t (*write)(struct file *file, const char __user *buf, size_t count, loff_t *data);
    ...
}

/* 从用户空间拷贝数据：linux/uaccess.h */
unsigned long copy_from_user(void *to, const void __user *from, unsigned long count);

/* 拷贝数据至用户空间：linux/uaccess.h */
unsigned long copy_to_user(void __user *to, const void *from, unsigned long count);

/* 字符串比较：string.h */
int strncmp(const char *str1, const char *str2, size_t n)
```

* 例：

```c
#define MAX_PROC_CMD_LEN 64
ssize_t myuart_proc_write(struct file *file, const char *buf, size_t count, loff_t *data)
{
  char cmd[MAX_PROC_CMD_LEN + 1] = {0};
  int real_len = count < MAX_PROC_CMD_LEN ? count : MAX_PROC_CMD_LEN;

  copy_from_user(cmd, buf, real_len);

  /* echo "xxx" > /proc/test */
  if (strncmp(cmd, "xxx", strlen("xxx")) == 0) {
      xxx();
  }
  ...

  return count;
}

static struct file_operations g_proc_fops = {
  .write = test_proc_write,
}

struct proc_dir_entry *g_entry = NULL;
statinc int test_probe(void)
{
  ...
  /* will create file: /proc/test */
  g_entry = proc_create("test", 0644, NULL, &g_proc_fops);
  if (g_entey == NULL) {
    printk("create proc file failed\n");
    return -1;
  }
  ...
}

static int test_remove(void)
{
  ...
  remove_proc_entry("test", NULL);
  ...
}
```

## 2、中断相关：

```c
/* 中断处理函数原型 */
typedef irqreturn_t (*irq_handler_t)(int irq, void *data);

/*
 * 中断注册：
 * irq: 终端号
 * handler: 中断处理函数
 * flag: 中断属性
 * name: 中断名称
 * data: 自定义数据
 */
static inline int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *data)

/* 中断释放 */
void free_irq(unsigned int irq, void *data)

/* 中断使能 */
void enable_irq(unsigned int irq);

/* 中断禁止 */
void disable_irq(unsigned int irq);
```

* 例：

```c
static irqreturn_t test_irq_handler(int irq, void *data)
{
  printk("Enter %s\n", __func__);
}

static int test_probe(void)
{
  int ret;
  ...
  ret = request_irq(g_irq, test_irq_handler, 0, "test", NULL);
  if (ret < 0) {
    printk("request irq failed\n");
    return ret;
  }
  ...
  disable_irq(g_irq);
  ...
  enable_irq(g_irq);
  ...
}

static void test_remove(void)
{
  ...
  free_irq(g_irq);
  ...
}
```