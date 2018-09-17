#!/bin/sh

if [ -z "$CLOUD_ROOT" ]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

sh "$CLOUD_ROOT"/docker/cpp/env/make.sh "$1"
sh "$CLOUD_ROOT"/docker/go/env/make.sh "$1"