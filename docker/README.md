# Docker instructions

## Buid

### Environment images
```
docker/cpp/env/make.sh
docker/go/env/make.sh
```

### Cloud binaries images
```
docker/cpp/bin/make.sh
docker/go/bin/make.sh
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