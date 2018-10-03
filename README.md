# Google Cloud Microservices C++

## Libraries and dependencies
* [Bazel 0.17.2](https://github.com/bazelbuild/bazel/releases/tag/0.17.2)
* [Protobuf 3.6.1](https://github.com/protocolbuffers/protobuf/releases/tag/v3.6.1)
* [gPRC 1.15.1](https://github.com/grpc/grpc/releases/tag/v1.15.1)
* [gTEST 1.8.1](https://github.com/google/googletest/releases/tag/release-1.8.1)
* [gLOG 0.3.5](https://github.com/google/glog/releases/tag/v0.3.5)
* [GoLang 1.10.4](https://github.com/golang/go/releases/tag/go1.10.4)

## Prerequirements

Add necessary environment variables:
```
. shell/env.sh
```

Next installation scripts checked on Ubuntu 18.04.

Install C++ dependencies:
```
sh cpp/install_dependencies.sh
```

Install Go dependencies:
```
sh go/install_dependencies.sh
```

## Build

Short pipeline script for building and testing C++ and Go binaries:
```
sh cpp/make_build.sh && sh cpp/make_test.sh
sh go/make_build.sh && sh go/make_test.sh
```

## Usage

### Run backend server
```
(export SERVER_NAME=WordCount; export SERVER_PORT=9001; $CLOUD_BIN/word_count_analyzer-server)
```

### Run frontend server
```
(export WORD_COUNT_ANALYZER_ADDRESS=localhost:9001; export FRONTEND_PORT=8080; $CLOUD_BIN/frontend-server)
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
0. Parse JSON.
1. Integration tests.
 - [gmock](https://github.com/google/googlemock/tree/master/googlemock)
2. Performance:
 - [Benchmark](https://github.com/google/benchmark)
3. Build system:
 - [Bazel](https://github.com/bazelbuild/bazel)
4. Deploy to Google Cloud.