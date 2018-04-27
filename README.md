# Cloud Finance Analyzer (CFA)

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

## Documentation

### Read

Open in your browser file `doc/html/index.html`

### Generate
```
doxygen doc/config.txt
```