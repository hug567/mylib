## 1、linux内核对象：

* kobject：内核对象，每个kobject对应sysfs中一个目录；

  常用接口：

  ```c
  kobject_init
  kobject_add
  kobject_init_and_add
  kobject_del
  kobject_get
  kobject_put
  ```

* kobj_type：记录kobject的一些属性，ktype中一个attribute对应sysfs中一个文件；

* kset：相同类型的kobject的集合，使用链表存储所有的kobject，热插拔通过kset_uevent_ops通知用户空间；

  kset也是一个kobject的派生类，其包含的成员kobj是对kobject的继承，与其成员list上存储的kobject无关；

  常用接口：
  
  ```c
  kset_init
  kset_register
  kset_unregister
  kset_get
  kset_put
  ```
  
## 2、linux驱动框架：

* bus_type: 总线，platform bus，linux虚拟的总线，通常连接soc的设备，cpu可通过常规寻址操作访问他们；

* device: 设备

* device_driver: 驱动

* class: 类，集合具有相似功能或属性的设备；