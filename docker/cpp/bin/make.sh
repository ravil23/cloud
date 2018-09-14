#!/bin/sh

if [ -z "$CLOUD_ROOT" ]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

IMAGE_NAME=cloud-cpp-bin
IMAGE_VERSION=$(git branch | grep \* | cut -d ' ' -f2)-$(git log -1 --format=%h)

docker build -t $IMAGE_NAME:$IMAGE_VERSION -f "$CLOUD_ROOT"/docker/cpp/bin/Dockerfile "$CLOUD_ROOT"
docker tag $IMAGE_NAME:$IMAGE_VERSION $IMAGE_NAME:latest