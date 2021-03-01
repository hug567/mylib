TOOLS_DIR=${HOME}/tools

IMAGE_NAME=huangxing/myopensuse
IMAGE_TAG=latest

docker run -it \
	-v ${MYLIB}:${MYLIB} \
	-v ${TOOLS_DIR}:${TOOLS_DIR} \
	${IMAGE_NAME}:${IMAGE_TAG} \
	/bin/bash
