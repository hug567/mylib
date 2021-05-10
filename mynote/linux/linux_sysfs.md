## 1、sysfs文件创建：

```c
/*
 * 创建并添加kobject: ./linux/kobject.h
 * name: 待创建的kobject的名称，即sys下：parent/name/目录，如：/sys/test/
 * parent: 父kobject, NULL代表: /sys
 */
struct kobject *kobject_create_and_add(const char *name, struct kobject *parent);

/*
 * 删除kobject: ./linux/kobject.h
 * kobj: 待删除的kobject
 * parent: 父kobject, NULL代表: /sys
 */
int kobject_move(struct kobject *kobj, struct kobject *parent);

/*
 * 属性结构体：./linux/sysfs.h
 * name: 属性名称，即sys下：kobj/attr_group/name文件, 如：/sys/test/test/test
 * mode: 属性模式，例：0644
 */
struct attribute {
        const char              *name;
        umode_t                 mode;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
        bool                    ignore_lockdep:1;
        struct lock_class_key   *key;
        struct lock_class_key   skey;
#endif
};


/*
 * kobject属性结构体：./linux/kobject.h
 * attr: kobject属性
 * show: 显示钩子函数
 * store: 存储钩子函数
 */
struct kobj_attribute {
        struct attribute attr;
        ssize_t (*show)(struct kobject *kobj, struct kobj_attribute *attr,
                        char *buf);
        ssize_t (*store)(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count);
};

/*
 * 属性组结构体：./linux/sysfs.h
 * name: 属性组名称，即sys下：kobj/name/目录，如：/sys/test/test/
 * attrs: 属性数组
 */
struct attribute_group {
        const char              *name;
        umode_t                 (*is_visible)(struct kobject *,
                                              struct attribute *, int);
        umode_t                 (*is_bin_visible)(struct kobject *,
                                                  struct bin_attribute *, int);
        struct attribute        **attrs;
        struct bin_attribute    **bin_attrs;
};

/*
 * 创建sysfs组：./linux/sysfs.h
 * kobj: 内核对象
 * grp: 属性组
 */
int sysfs_create_group(struct kobject *kobj, const struct attribute_group *grp);

/*
 * 移除属性组：./linux/sysfs.h
 * kobj: 内核对象
 * grp: 属性组
 */
void sysfs_remove_group(struct kobject *kobj, const struct attribute_group *grp);
```

* 例：

```c
static ssize_t test_sysfs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        return sprintf(buf, "Enter %s\n", __func__);
}

static ssize_t test_sysfs_store(struct kobject *kobj, struct kobj_attribute *attr,
                                  const char *buf, size_t count)
{
        printk("buf: %s\n", buf);
        return count;
}

/* 将创建sysfs文件：/sys/test_obj/test_group/test_file */
static struct kobj_attribute g_kobj_attr = {
        .attr.name = "test_file",
        .attr.mode = 0644,
        .show = test_sysfs_show,
        .store = test_sysfs_store,
};

static struct attribute *g_sys_attrs[] = {
        &g_kobj_attr.attr,
        NULL,
};

static struct attribute_group g_sys_attr_group = {
        .name = "test_group",
        .attrs = g_sys_attrs,
};

static struct kobject *g_test_kobj = NULL;

static int test_sysfs_probe(struct myuart *myuart)
{
        int ret;

        g_test_kobj = kobject_create_and_add("test_obj", NULL);
        if (g_test_kobj == NULL) {
                printk("kobject_create_and_add failed\n");
                return -1;
        }

        ret = sysfs_create_group(g_test_kobj, &g_sys_attr_group);
        if (ret < 0) {
                printk("sysfs_create_group failed\n");
                ret = kobject_move(g_test_kobj, NULL);
                return ret;
        }

        return 0;
}

static int test_sysfs_remove(void)
{
        int ret;
        sysfs_remove_group(g_test_kobj, &g_sys_attr_group);
        ret = kobject_move(g_test_kobj, NULL);
        return ret;
}
```