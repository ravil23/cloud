#!/bin/sh

# Clean created containers and network
docker stop cloud-frontend
docker stop cloud-word_count
docker network rm cloud-net
