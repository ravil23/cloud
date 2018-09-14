#!/bin/sh

if [ -z "$GOPATH" ]; then
  echo "ERROR: Environment variable GOPATH not found." 1>&2
  exit 1
fi

go get -v github.com/golang/protobuf/{proto,protoc-gen-go}
go get -v google.golang.org/grpc
go get -v github.com/google/uuid