# Docker instructions

## Buid

### Environment image
```
docker/env/make.sh
```

### Cloud binaries image
```
docker/bin/make.sh
```

## Usage

### Create network
```
docker network create --driver bridge cloud-net
```

### Run backend server
```
docker run -d --rm \
    --name cloud-server \
    --network cloud-net \
    -e SERVER_NAME=WordCount \
    -e SERVER_PORT=9001 \
    cloud-bin \
    bin/word_count-server
```

### Run frontend server
```
docker run -d --rm \
    --name cloud-client \
    --network cloud-net \
    cloud-bin
```

### Clean created containers and network
```
docker stop cloud-server cloud-client
docker network rm cloud-net
```