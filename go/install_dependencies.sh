#!/bin/sh

apt-get update && apt-get install -y protobuf-compiler

go get -v github.com/golang/protobuf/{proto,protoc-gen-go}
go get -v google.golang.org/grpc
go get -v github.com/google/uuid