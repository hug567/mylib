# print log in recipe

# 匿名函数打印调试信息
python() {
    bb.note("[hx-debug] hello world")  # 使用空格缩进
    bb.plain("[hx-debug] xxx")
    bb.note("[hx-debug] PN = %s" % d.getVar('PN'))
    bb.warn("[hx-debug] PN = %s" % d.getVar('PN'))  # warn级别打印
    bb.error("[hx-debug] xxx")

    # 只能打印一行时：
    bb.note("\n[hx-debug]:\n",
        "KERNEL_DEBUG_OPTIONS = %s" % d.getVar("KERNEL_DEBUG_OPTIONS"), "\n",
        "KBRANCH = %s" % d.getVar("KBRANCH"), "\n",
    )
}

# 在.bbclass文件函数中打印变量，需加大括号
bbnote "[hx-debug] S = ${S}"

#------------------------------------------------------------------------------#
# poky 2.2.2: meta-poky/conf/distro/poky.conf
bb.note("[hx-debug] S = %s" % d.getVar('S', True))

python() {
    bb.note("\n[hx-debug]:\n",
        "S = %s" % d.getVar("S", True), "\n",
        "B = %s" % d.getVar("B", True), "\n",
        "D = %s" % d.getVar("D", True), "\n",
    )
}
