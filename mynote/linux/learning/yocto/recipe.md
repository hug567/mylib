# 1、任务常用设置：

## 1）、自定义任务：

```bash
# 不执行某个任务
do_rm_work[noexec] = "1"

# 强制每次均执行某个任务
do_configure[nostap] = "1"

# 在recipe的各任务间插入自定义任务，如：
addtask my_deploy after do_install
addtask my_install before do_install after do_compile
```

## 2）、运行时修改变量值：

```bash
python() {
    topdir = d.getVar("TOPDIR", True)
    rmachine = d.getVar("RHOSOONMACHINE", True)
    hdir = os.path.abspath(topdir + "/../project-spec/hw-description/" + rmachine)
    hpath = os.path.join(hdir, "system.hdf")
    d.setVar('HDF_PATH', hpath) # 编译recpie前修改变量HDF_PATH的值
}
```

