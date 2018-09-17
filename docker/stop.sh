#!/bin/sh

# Clean created containers and network
docker stop cloud-word_count cloud-frontend
docker network rm cloud-net