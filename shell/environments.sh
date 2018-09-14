#!/bin/sh

export CLOUD_ROOT="$(pwd)/$(dirname "$0")/.."
export CLOUD_BUILD="$CLOUD_ROOT"/build
export CLOUD_BINARY="$CLOUD_BUILD"/bin
export GOPATH="$CLOUD_ROOT"/go
export PATH="$PATH:$GOPATH/bin"