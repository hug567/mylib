# 1、petalinux-create：
```bash
petalinux-create
	-h                                  # 查看帮助
    -t <type>                           # 指定类型(project/apps/modules)
    -n <name>                           # 指定工程或组件名称
	--force                             # 强制覆盖已存在的文件
	--enable                            # 使能已创建的组件
	--template <temp>                   # 指定模板(zynqMP/zynq/microblaze)
	-s <dir>                            # 指定一个petalinux BSP作为工程来源

# 基于petalinux BSP创建工程
petalinux-create -t project -s <PATH_TO_PETALINUX_PROJECT_BSP>
# 基于模板创建工程
petalinux-create -t project -n <PROJECT> --template zynq
# 创建一个应用并使能: <PROJECT>/project-spec/meta-user/recipes-apps/myapp
petalinux-create -t apps -n myapp --enable
# 创建一个内核模块并使能：<PROJECT>/project-spec/meta-user/recipes-modules/mymodule
petalinux-create -t modules -n mymodule --enable
```

# 2、petalinux-config：

```bash
petalinux-config
	-h                                  # 查看帮助
	-p <dir>                            # 配置指定目录中的工程，默认当前目录
	-c <component>                      # 配置组件
	--oldconfig                         # 使用已生成的配置文件
	--get-hw-description <dir>          # 获取硬件信息(hdf文件)
	--defconfig <file>                  # 配置指定组件，仅对kernel有效
	-v                                  # 详情模式

# 从指定目录获取硬件信息
petalinux-config --get-hw-description <dir>
# 打开顶层配置
petalinux-config
# 配置kernel
petalinux-config -c kernel
# 配置rootfs
petalinux-config -c rootfs
```

# 3、petalinux-build：

```bash
petalinux-build
	-h                                  # 查看帮助
	-p <dir>                            # 构建指定目录中的工程，默认当前目录
	-c <component>                      # 构建指定组件
	-x <task>                           # 构建一个指定的bitbake task
	-f                                  # 强制执行
	-v                                  # 详情模式

# 构建整个工程
petalinux-build
# 只构建kernel
petalinux-build -c kernel
# 强制执行kernel编译
petalinux-build -c kernel -x compile -f
# 强制执行kernel部署
petalinux-build -c kernel -x deploy -f
# 构建kernel后更新启动镜像
petalinux-build -c kernel
petalinux-build -x package
# 只构建rootfs
petalinux-build -c rootfs
# 只构建rootfs中的myapp
petalinux-build -c rootfs/myapp
# 列出rootfs中的所有子组件
petalinux-build -c rootfs -h
# 清除u-boot并重新构建
petalinux-build -c u-boot -x distclean
petalinux-build -c u-boot
# 清除整个工程并重新构建
petalinux-build -x distclean
petalinux-build
# 清除工程构建与生成的启动镜像
petalinux-build -x mrproper
```

# 4、petalinux-package：

```bash
petalinux-package
	-h                                  # 查看帮助
	--boot|--bsp|--image|--prebuilt     # 打包组件

# 查看boot选项帮助
petalinux-package --boot --help
# 查看bsp选项帮助
petalinux-package --bsp --help
# 查看image选项帮助
petalinux-package --image --help
# 查看prebuilt选项帮助
petalinux-package --prebuilt --help
```

