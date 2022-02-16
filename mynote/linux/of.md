# Linux of 框架学习

## 1、基本概念：

```c
of: open firmware, 开放固件
dts: device tree source, 设备树源文件
dtb: device tree binary, 设备树二进制文件
dtc: device tree compiler, 设备树编译器
```

## 2、主要数据结构：

### 1）、struct device_node

```c
struct device_node {
        const char *name;       //设备节点名称
        const char *type;       //设备节点类型
        phandle phandle;        //phandle值
        const char *full_name;  //设备节点全路径名称
        struct fwnode_handle fwnode;

        struct  property *properties;
        struct  property *deadprops;    /* removed properties */
        struct  device_node *parent;
        struct  device_node *child;
        struct  device_node *sibling;
#if defined(CONFIG_OF_KOBJ)
        struct  kobject kobj;
#endif
        unsigned long _flags;
        void    *data;
#if defined(CONFIG_SPARC)
        const char *path_component_name;
        unsigned int unique_id;
        struct of_irq_controller *irq_trans;
#endif
};
```

