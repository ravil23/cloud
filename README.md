# Google Cloud Microservices C++

## Libraries and dependencies
* [Bazel 0.18.0](https://github.com/bazelbuild/bazel/releases/tag/0.18.0)
* [Protobuf 3.6.1](https://github.com/protocolbuffers/protobuf/releases/tag/v3.6.1)
* [gPRC 1.15.1](https://github.com/grpc/grpc/releases/tag/v1.15.1)
* [gTEST 1.8.1](https://github.com/google/googletest/releases/tag/release-1.8.1)
* [gLOG 0.3.5](https://github.com/google/glog/releases/tag/v0.3.5)
* [GoLang 1.10.4](https://github.com/golang/go/releases/tag/go1.10.4)

## Prerequirements

[Install Bazel](https://docs.bazel.build/versions/master/install.html)

## Build

Short pipeline script for building and testing C++ and Go binaries:
```
bazel build //...
bazel run //cpp/analyzers/word_count:word_count_analyzer_test
```

## Usage

### Run backend server
```
(export SERVER_NAME=WordCount; export SERVER_PORT=9001; bazel run //cpp/analyzers/word_count:word_count_analyzer_server)
```

### Run frontend server
```
(export WORD_COUNT_ANALYZER_ADDRESS=localhost:9001; export FRONTEND_PORT=8080; bazel run //go/request_handler:request_handler)
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
0. Bazel workspace over HTTP archive.
1. Bazel go build.
2. Parse JSON in request_handler.
3. Integration tests.
 - [gmock](https://github.com/google/googlemock/tree/master/googlemock)
4. Performance:
 - [Benchmark](https://github.com/google/benchmark)
5. Deploy to Google Cloud.
