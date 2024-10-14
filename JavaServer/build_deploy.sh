#!/bin/sh

IMAGE_NAME=test
CONTAINER_NAME=javaserver
HOST_PORT=8000
CONTAINER_PORT=1234
CONTAINER_IMAGES_DIR="/app/images"
IMAGES_DIR="/home/user/Projects/STM32CubeIDE/workspace_1.16.1/FOTA-AWS/JavaServer/test/"

docker run --rm -d -p $HOST_PORT:$CONTAINER_PORT -e IMAGES_DIR=/app/images -v $IMAGES_DIR:$CONTAINER_IMAGES_DIR --name ${CONTAINER_NAME} ${IMAGE_NAME}