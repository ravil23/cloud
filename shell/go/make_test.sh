#!/bin/sh

if [ -z "$CLOUD_ROOT" ]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

if [ -z "$GOPATH" ]; then
  echo "ERROR: Environment variable GOPATH not found." 1>&2
  exit 1
fi

# Test frontend
cp -r "$CLOUD_ROOT"/go/src/frontend/ "$GOPATH"/src/ \
  && go test frontend/ \
  && rm -r "$GOPATH"/src/frontend/
