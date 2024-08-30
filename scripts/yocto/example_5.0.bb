# recipe样例
# yocto版本：5.0
# 2024-08-30

SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by bitbake-layers"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI = "file://hello.c \
          "

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

do_fetch:prepand() {
    if [ ! -d ${S} ]; then
        mkdir -p ${S}
    fi
}

do_compile() {
    ${CC} ${WORKDIR}/sources-unpack/hello.c
}
