#!/bin/bash

BUILD_DIR=build-bin

if [ ! -d ${BUILD_DIR} ];then
	mkdir ${BUILD_DIR}
fi

cp -r Makefile ${BUILD_DIR}
cp -r leetcode ${BUILD_DIR}
cp -r build.sh ${BUILD_DIR}
cp -r clean.sh ${BUILD_DIR}
cd ${BUILD_DIR}
make build
