#!/bin/sh

IMAGE_TAG="$1"

if [ -z "$IMAGE_TAG" ]; then
  IMAGE_TAG=latest
fi

# Create network
docker network create --driver bridge cloud-net

# Run backend servers
docker run -d --rm \
    --name cloud-word_count \
    --network cloud-net \
    -e SERVER_NAME=WordCount \
    -e SERVER_PORT=9001 \
    cloud-cpp-bin:$IMAGE_TAG \
    bin/word_count-server

# Run frontend server
docker run -d --rm \
    --name cloud-frontend \
    --network cloud-net \
    -e WORD_COUNT_ANALYZER_ADDRESS=localhost:9001 \
    -e FRONTEND_PORT=8080 \
    cloud-go-bin:$IMAGE_TAG \
    bin/frontend-server