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
bin/protobuf-writer AnalyzerInput 3 | bin/analyzer-client 0.0.0.0:9001 | bin/protobuf-reader AnalyzerOutput json
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

### Unique Inputs Counter

Run server:
```
docker run -it --rm -e SERVER_NAME=UniqueInputsCounter -e SERVER_PORT=9001 -p 9001:9001 cloud-build bin/unique_inputs_counter-server
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
