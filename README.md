# Google Cloud Microservices C++

## Libraries and dependecies
* [CMake](https://cmake.org/)
* [Protobuf 3](https://github.com/google/protobuf)
* [grpc](https://github.com/grpc/grpc)
* [gtest](https://github.com/google/googletest)
* [glog](https://github.com/google/glog)

## Local instructions

### Prerequirements

See `docker/env/Dockerfile` for dependecies installation on Ubuntu.

### Build source

All binaries collected in folder `build/bin` after executing commands:
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make all -j8
ctest
```

### Usage examples

All commands run from build directory.

#### Run server
```
export SERVER_NAME=UniqueInputsCounter; \
export SERVER_PORT=9001; \
bin/unique_inputs_counter-server
```

#### Run client
```
bin/protobuf-writer AnalyzerInput 3 \
    | bin/analyzer-client 0.0.0.0:9001 \
    | bin/protobuf-reader AnalyzerOutput json
```

## Docker instructions

### Buid Environment image
```
docker/env/make.sh
```

### Buid Cloud binaries image
```
docker/bin/make.sh
```

### Usage examples

Create network:
```
docker network create --driver bridge cloud-net
```

#### Run server
```
docker run -dit --rm \
    --name cloud-server \
    --network cloud-net \
    -e SERVER_NAME=UniqueInputsCounter \
    -e SERVER_PORT=9001 \
    cloud-bin \
    bin/unique_inputs_counter-server
```

#### Run client
```
docker run -dit --rm \
    --name cloud-client \
    --network cloud-net \
    cloud-bin
docker exec -i cloud-client bin/protobuf-writer AnalyzerInput 3 \
    | docker exec -i cloud-client bin/analyzer-client cloud-server:9001 \
    | docker exec -i cloud-client bin/protobuf-reader AnalyzerOutput json
```

#### Clean created containers and network
```
docker stop cloud-server cloud-client
docker network rm cloud-net
```

## Documentation

### Read

Open in your browser file `doc/html/index.html`

### Generate
```
doxygen doc/config.txt
```

## TODO
1. Add comments.
2. Refactor protobuf reader/writer tool.
3. Secure gRPC.
4. Add manager.
5. Hosting Travis/Appveyor.
6. [Bazel](https://github.com/bazelbuild/bazel)
7. [Benchmark](https://github.com/google/benchmark)
8. [Grafana](https://github.com/grafana/grafana)
