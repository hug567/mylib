#!/bin/bash

SOURCE_FILE='main.c '
SOURCE_FILE+='test.h '
SOURCE_FILE+='Makefile '
SOURCE_FILE+='string '

if [ $# != 1 ]; then
	echo "need to input build directory"
	exit
fi

BUILD_DIR=$1
if [ ! -d ${BUILD_DIR} ]; then
	echo "${BUILD_DIR} does not exist"
	exit
fi

cp -r ${SOURCE_FILE} ${BUILD_DIR}

