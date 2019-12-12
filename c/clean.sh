#!/bin/bash


BUILD_DIR=build-bin

if [ ! -d ${BUILD_DIR} ];then
	mkdir ${BUILD_DIR}
fi

cd ${BUILD_DIR}

make clean
