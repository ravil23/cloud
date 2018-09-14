#!/bin/sh

# Clean created containers and network
docker stop cloud-wordcount cloud-frontend
docker network rm cloud-net