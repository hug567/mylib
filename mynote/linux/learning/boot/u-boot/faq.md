## 1、常见错误：

### 1）、gcc版本问题：

```c
/home/hx/code/linux/u-boot/include/linux/compiler-gcc.h:93:1: fatal error: linux/compiler-gcc7.h: No such file or directory
 #include gcc_header(__GNUC__)
 ^~~~
compilation terminated.
```

* 原因：gcc版本超过4（注：\__GNUC__为gcc定义的主版本号宏）

* 解决：指定gcc版本为4

```c
diff --git a/include/linux/compiler-gcc.h b/include/linux/compiler-gcc.h
index 9896e547b9..c08ba74b26 100644
--- a/include/linux/compiler-gcc.h
+++ b/include/linux/compiler-gcc.h
@@ -90,4 +90,4 @@
 #define __gcc_header(x) #x
 #define _gcc_header(x) __gcc_header(linux/compiler-gcc##x.h)
 #define gcc_header(x) _gcc_header(x)
-#include gcc_header(__GNUC__)
+#include gcc_header(4)
```

### 2）、inline别名问题：

```c
board.c:66:6: error: ‘coloured_LED_init’ aliased to external symbol ‘__coloured_LED_init’
 void coloured_LED_init(void)
      ^~~~~~~~~~~~~~~~~
board.c:83:6: error: ‘blue_led_off’ aliased to external symbol ‘__blue_led_off’
 void blue_led_off(void) __attribute__((weak, alias("__blue_led_off")));
      ^~~~~~~~~~~~
board.c:81:6: error: ‘blue_led_on’ aliased to external symbol ‘__blue_led_on’
 void blue_led_on(void) __attribute__((weak, alias("__blue_led_on")));
      ^~~~~~~~~~~
board.c:79:6: error: ‘yellow_led_off’ aliased to external symbol ‘__yellow_led_off’
 void yellow_led_off(void) __attribute__((weak, alias("__yellow_led_off")));
      ^~~~~~~~~~~~~~
board.c:77:6: error: ‘yellow_led_on’ aliased to external symbol ‘__yellow_led_on’
 void yellow_led_on(void) __attribute__((weak, alias("__yellow_led_on")));
      ^~~~~~~~~~~~~
board.c:75:6: error: ‘green_led_off’ aliased to external symbol ‘__green_led_off’
 void green_led_off(void) __attribute__((weak, alias("__green_led_off")));
      ^~~~~~~~~~~~~
board.c:73:6: error: ‘green_led_on’ aliased to external symbol ‘__green_led_on’
 void green_led_on(void) __attribute__((weak, alias("__green_led_on")));
      ^~~~~~~~~~~~
board.c:71:6: error: ‘red_led_off’ aliased to external symbol ‘__red_led_off’
 void red_led_off(void) __attribute__((weak, alias("__red_led_off")));
      ^~~~~~~~~~~
board.c:69:6: error: ‘red_led_on’ aliased to external symbol ‘__red_led_on’
 void red_led_on(void) __attribute__((weak, alias("__red_led_on")));
      ^~~~~~~~~~
```

* 原因：inline函数不能添加弱符号别名

* 解决：指定弱符号别名的函数删除inline

```c
diff --git a/arch/arm/lib/board.c b/arch/arm/lib/board.c
index b770e25d87..ec4e478bfc 100644
--- a/arch/arm/lib/board.c
+++ b/arch/arm/lib/board.c
@@ -62,24 +62,24 @@ extern void dataflash_print_info(void);
  ************************************************************************
  * May be supplied by boards if desired
  */
-inline void __coloured_LED_init(void) {}
+void __coloured_LED_init(void) {}
 void coloured_LED_init(void)
        __attribute__((weak, alias("__coloured_LED_init")));
-inline void __red_led_on(void) {}
+void __red_led_on(void) {}
 void red_led_on(void) __attribute__((weak, alias("__red_led_on")));
-inline void __red_led_off(void) {}
+void __red_led_off(void) {}
 void red_led_off(void) __attribute__((weak, alias("__red_led_off")));
-inline void __green_led_on(void) {}
+void __green_led_on(void) {}
 void green_led_on(void) __attribute__((weak, alias("__green_led_on")));
-inline void __green_led_off(void) {}
+void __green_led_off(void) {}
 void green_led_off(void) __attribute__((weak, alias("__green_led_off")));
-inline void __yellow_led_on(void) {}
+void __yellow_led_on(void) {}
 void yellow_led_on(void) __attribute__((weak, alias("__yellow_led_on")));
-inline void __yellow_led_off(void) {}
+void __yellow_led_off(void) {}
 void yellow_led_off(void) __attribute__((weak, alias("__yellow_led_off")));
-inline void __blue_led_on(void) {}
+void __blue_led_on(void) {}
 void blue_led_on(void) __attribute__((weak, alias("__blue_led_on")));
-inline void __blue_led_off(void) {}
+void __blue_led_off(void) {}
 void blue_led_off(void) __attribute__((weak, alias("__blue_led_off")));
```

### 3）、符号重复定义：

```c
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `__raw_writesb':
/home/hx/code/linux/u-boot/arch/arm/include/asm/io.h:80: multiple definition of `__raw_writesb'                                                     /home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_bootm.o:/home/hx/code/linux/u-boot/arch/arm/include/asm/io.h:80: first defined here
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `fdt_valid':                                                             /home/hx/code/linux/u-boot/common/cmd_fdt.c:608: multiple definition of `__raw_writesw'
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_bootm.o:/home/hx/code/linux/u-boot/common/cmd_bootm.c:1461: first defined here
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `fdt_valid':
/home/hx/code/linux/u-boot/common/cmd_fdt.c:608: multiple definition of `__raw_writesl'
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_bootm.o:/home/hx/code/linux/u-boot/common/cmd_bootm.c:1461: first defined here
/home/hx/code/linux/u-boot/build-vexpress_a9/common/cmd_fdt.o: In function `fdt_valid':
......
```

* 原因：头文件中inline函数声明为extern

* 解决：删除.h文件中inline函数的extern

```c
diff --git a/arch/arm/include/asm/io.h b/arch/arm/include/asm/io.h
index 6a1f05ac3e..0e64e7cf4f 100644
--- a/arch/arm/include/asm/io.h
+++ b/arch/arm/include/asm/io.h
@@ -75,7 +75,7 @@ static inline phys_addr_t virt_to_phys(void * vaddr)
 #define __arch_putw(v,a)               (*(volatile unsigned short *)(a) = (v))
 #define __arch_putl(v,a)               (*(volatile unsigned int *)(a) = (v))

-extern inline void __raw_writesb(unsigned long addr, const void *data,
+inline void __raw_writesb(unsigned long addr, const void *data,
                                 int bytelen)
 {
        uint8_t *buf = (uint8_t *)data;
@@ -83,7 +83,7 @@ extern inline void __raw_writesb(unsigned long addr, const void *data,
                __arch_putb(*buf++, addr);
 }

-extern inline void __raw_writesw(unsigned long addr, const void *data,
+inline void __raw_writesw(unsigned long addr, const void *data,
                                 int wordlen)
 {
        uint16_t *buf = (uint16_t *)data;
@@ -91,7 +91,7 @@ extern inline void __raw_writesw(unsigned long addr, const void *data,
                __arch_putw(*buf++, addr);
 }

-extern inline void __raw_writesl(unsigned long addr, const void *data,
+inline void __raw_writesl(unsigned long addr, const void *data,
                                 int longlen)
 {
        uint32_t *buf = (uint32_t *)data;
@@ -99,21 +99,21 @@ extern inline void __raw_writesl(unsigned long addr, const void *data,
                __arch_putl(*buf++, addr);
 }
......
```

### 4）、设置mac地址失败

* 原因：未使能CONFIG_ENV_OVERWRITE
* 解决：在config文件中使能CONFIG_ENV_OVERWRITE=y后，重新编译

```bash
=> setenv ethaddr 00:04:9f:04:d2:35
## Error: Can't overwrite "ethaddr"
## Error inserting "ethaddr" variable, errno=1
```

