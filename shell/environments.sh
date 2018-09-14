#!/bin/sh

export CLOUD_ROOT="$(pwd)/$(dirname "$0")/.."
export CLOUD_BUILD="$CLOUD_ROOT"/build
export CLOUD_BIN="$CLOUD_BUILD"/bin
export CLOUD_LIB="$CLOUD_BUILD"/lib
export GOPATH="$CLOUD_ROOT"/go
export PATH="$PATH:$GOPATH/bin"