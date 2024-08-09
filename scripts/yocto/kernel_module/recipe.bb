SUMMARY = "build linux drivers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI = "git://${TOPDIR}/../../linux-drivers;protocol=file;usehead=1"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"
B = "${WORKDIR}/git"
D = "${WORKDIR}/image"

DEPENDS = "linux-xlnx"

inherit module

FILES_${PN} += " /lib/modules"
