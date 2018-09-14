#!/bin/sh

SCRIPT_DIR=$(pwd)/$(dirname "$0")
IMAGE_NAME=cloud-env
IMAGE_VERSION=$(git branch | grep \* | cut -d ' ' -f2)-$(git log -1 --format=%h)

docker build -t $IMAGE_NAME:$IMAGE_VERSION -f "$SCRIPT_DIR/Dockerfile" "$SCRIPT_DIR/../.."
docker tag $IMAGE_NAME:$IMAGE_VERSION $IMAGE_NAME:latest