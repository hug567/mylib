## 1、.config文件编译：

```c
/*
 * file：scripts/kconfig/Makefile
 * obj = scripts/kconfig
 * Q = @
 * silent = 
 * SRCARCH = arm
 * Kconfig = Kconfig
 */
%_defconfig: $(obj)/conf
    $(Q)$< $(silent) --defconfig=arch/$(SRCARCH)/configs/$@ $(Kconfig)
```

## 2、Linux Makefile组成：

Makefile    顶层Makefile

.config    内核配置文件

arch/$(ARCH)/Makefile    具体架构的Makefile

scripts/Makefile.*    通用规则等，面向所有的Kbuild Makefiles

Kbuild Makefiles    具体文件的编译规则

## 3、编驱动模块时引入驱动模块的Makefile：

```c
/*
 * file: scripts/Makefile.modpost
 * KBUILD_EXTMOD=../your/own/dirver/dir
 */
# Include the module's Makefile to find KBUILD_EXTRA_SYMBOLS
include $(if $(wildcard $(KBUILD_EXTMOD)/Kbuild), \
                        $(KBUILD_EXTMOD)/Kbuild, $(KBUILD_EXTMOD)/Makefile)
```

