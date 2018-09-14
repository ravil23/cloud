#!/bin/sh

if [[ -z "$CLOUD_ROOT" ]]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

if [[ -z "$CLOUD_BINARY" ]]; then
  echo "ERROR: Environment variable CLOUD_BINARY not found." 1>&2
  exit 1
fi

if [[ -z "$GOPATH" ]]; then
  echo "ERROR: Environment variable GOPATH not found." 1>&2
  exit 1
fi

# Update generated files
PROTO_INPUT_DIR="$CLOUD_ROOT"/protobuf
PROTO_GO_OUT_DIR="$GOPATH"/src/protobuf

if [[ -d "$PROTO_GO_OUT_DIR" ]]; then
  rm -r "$PROTO_GO_OUT_DIR"
fi
mkdir "$PROTO_GO_OUT_DIR"

protoc -I "$PROTO_INPUT_DIR" --go_out=plugins=grpc:"$PROTO_GO_OUT_DIR" "$PROTO_INPUT_DIR"/*.proto

# Build binaries
mkdir -p "$CLOUD_BINARY"

go build -o "$CLOUD_BINARY"/frontend-server "$GOPATH"/src/frontend/
