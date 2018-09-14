#!/bin/sh

if [[ -z "$CLOUD_BUILD" ]]; then
  echo "ERROR: Environment variable CLOUD_BUILD not found." 1>&2
  exit 1
fi

make -C "$CLOUD_BUILD" test