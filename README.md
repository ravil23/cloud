# Cloud Microservices C++

## Libraries and dependecies
* [CMake](https://cmake.org/)
* [Protobuf 3](https://github.com/google/protobuf)
* [gRPC](https://github.com/grpc/grpc)
* [gtest](https://github.com/google/googletest)
* [glog](https://github.com/google/glog)

## Building

All binaries collected in folder 'build/bin' after executing commands:
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make all -j20
ctest
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

Run client:
```
bin/analyzer-client 0.0.0.0:9001 1 2 3 4 5
```

## Documentation

### Read

Open in your browser file `doc/html/index.html`

### Generate
```
doxygen doc/config.txt
```

## TODO
0. Read/Write data from/to stream.
1. Docker images for build and for deploy.
2. Hosting Travis/Appveyor.
3. Secure gRPC.