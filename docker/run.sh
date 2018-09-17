#!/bin/sh

# Create network
docker network create --driver bridge cloud-net

# Run backend servers
docker run -d --rm \
    --name cloud-word_count \
    --network cloud-net \
    -e SERVER_NAME=WordCount \
    -e SERVER_PORT=9001 \
    cloud-cpp-bin \
    bin/word_count-server

# Run frontend server
docker run -d --rm \
    --name cloud-frontend \
    --network cloud-net \
    -e WORD_COUNT_ANALYZER_ADDRESS=localhost:9001 \
    -e FRONTEND_PORT=8080 \
    cloud-go-bin \
    bin/frontend-server