# Google Cloud Microservices C++

## Libraries and dependecies
* [CMake](https://cmake.org/)
* [Protobuf 3](https://github.com/google/protobuf)
* [grpc](https://github.com/grpc/grpc)
* [gtest](https://github.com/google/googletest)
* [glog](https://github.com/google/glog)

## Building

All binaries collected in folder 'build/bin' after executing commands:
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make all -j8
ctest
```

## Docker

### Buid Environment image
```
docker/env/make.sh
```

### Buid Cloud image
```
docker/build/make.sh
```

## Usage examples

All commands run from build directory.

### Unique Inputs Counter

Run server:
```
export SERVER_NAME=UniqueInputsCounter; \
export SERVER_PORT=9001; \
bin/unique_inputs_counter-server
```
or
```
docker run -it --rm -e SERVER_NAME=UniqueInputsCounter -e SERVER_PORT=9001 -p 9001:9001 cloud-bin bin/unique_inputs_counter-server
```

Run client:
```
bin/protobuf-writer AnalyzerInput 3 | bin/analyzer-client 0.0.0.0:9001 | bin/protobuf-reader AnalyzerOutput json
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
6. Docker Network.
7. [Bazel](https://github.com/bazelbuild/bazel)
8. [Benchmark](https://github.com/google/benchmark)
9. [Grafana](https://github.com/grafana/grafana)
