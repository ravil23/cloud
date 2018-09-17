#!/bin/sh

if [ -z "$CLOUD_ROOT" ]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

IMAGE_TAG="$1"

if [ -z "$IMAGE_TAG" ]; then
  IMAGE_TAG=latest
fi

IMAGE_NAME=cloud-go-bin

docker build -t $IMAGE_NAME:$IMAGE_TAG -f "$CLOUD_ROOT"/docker/go/bin/Dockerfile "$CLOUD_ROOT"