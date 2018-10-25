#!/bin/sh

if [ -z "$GOROOT" ]; then
  echo "ERROR: Environment variable GOROOT not found." 1>&2
  exit 1
fi

if [ -z "$GOPATH" ]; then
  echo "ERROR: Environment variable GOPATH not found." 1>&2
  exit 1
fi

GOLANG_VERSION=1.10
apt-get update && apt-get install -y \
  protobuf-compiler \
  golang-$GOLANG_VERSION-go \
  git

ln -s /usr/lib/go-$GOLANG_VERSION $GOROOT

go get -v github.com/golang/protobuf/proto
go get -v github.com/golang/protobuf/protoc-gen-go
go get -v google.golang.org/grpc
go get -v github.com/google/uuid
