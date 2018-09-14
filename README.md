# Google Cloud Microservices C++

## Libraries and dependencies
* [CMake 3.10.2](https://github.com/Kitware/CMake/releases/tag/v3.10.2)
* [Protobuf 3.6.1](https://github.com/protocolbuffers/protobuf/releases/tag/v3.6.1)
* [gPRC 1.14.2](https://github.com/grpc/grpc/releases/tag/v1.14.2)
* [gTEST 1.8.1](https://github.com/google/googletest/releases/tag/release-1.8.1)
* [gLOG 0.3.5](https://github.com/google/glog/releases/tag/v0.3.5)

## Prerequirements

Add necessary environment variables:
```
source shell/environments.sh
```

Install dependencies:
```
sh shell/install_dependencies.sh
```

P.S. See `docker/env/Dockerfile` for C++ dependecies installation instructions.

## Build

Short pipeline script for building and testing C++ and Go binaries:
```
sh shell/build_pipeline.sh
```

## Usage

### Run backend server
```
(export SERVER_NAME=WordCount; export SERVER_PORT=9001; $CLOUD_BINARY/word_count_analyzer-server)
```

### Run frontend server
```
(export WORD_COUNT_ANALYZER_ADDRESS=localhost:9001; export FRONTEND_PORT=8080; $CLOUD_BINARY/frontend-server)
```

### Send HTTP request
```
curl -X POST -d "hello world hello" http://localhost:8080/word_count
```

## Documentation

### Read

Open in your browser file `docs/html/index.html`

### Generate
```
doxygen docs/config.txt
```

## TODO
0. Refactor C++ and Go.
1. Integration tests.
 - [gmock](https://github.com/google/googlemock/tree/master/googlemock)
2. Performance:
 - [Benchmark](https://github.com/google/benchmark)
3. Build system:
 - [Bazel](https://github.com/bazelbuild/bazel)
4. Update Docker images.
5. Deploy to Google Cloud.
