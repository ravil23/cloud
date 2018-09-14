#!/bin/sh

if [[ -z "$CLOUD_ROOT" ]]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

sh "$CLOUD_ROOT"/cpp/make_build.sh && sh "$CLOUD_ROOT"/cpp/make_test.sh

sh "$CLOUD_ROOT"/go/make_build.sh && sh "$CLOUD_ROOT"/go/make_test.sh
