## 1、linux驱动框架：

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

* kset：相同类型的kobject的集合，使用链表存储所有的kobject；

  kset也是一个kobject的派生类，其包含的成员kobj是对kobject的继承，与其成员list上存储的kobject无关；

  常用接口：
  
  ```c
  kset_init
  kset_register
  kset_unregister
  kset_get
  kset_put
  ```

