SUMMARY = "build linux drivers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://${TOPDIR}/../../linux-drivers;protocol=file;usehead=1"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/git"
D = "${WORKDIR}/image"

DEPENDS = "virtual/kernel"

inherit module

BB_DONT_CACHE = "1"

do_install_append() {
    install -d ${D}${sysconfdir}/init.d
    install -d ${D}${sysconfdir}/rcS.d
    install -m 0755 ${S}/etc/init.d/insmod_ko.sh ${D}${sysconfdir}/init.d
    install -m 0777 ${S}/etc/rcS.d/S42insmodko ${D}${sysconfdir}/rcS.d
}

do_fetch[nostamp] = "1"
do_compile[nostamp] = "1"
do_install[nostamp] = "1"

do_rm_work[noexec] = "1"

RDEPENDS_${PN} = "bash"
RPROVIDES_${PN} += "kernel-module-cpu0-sync-4.19.0-xilinx-v2019.1"
FILES_${PN} += "${sysconfdir} ${base_libdir}/modules"
