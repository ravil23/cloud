#!/bin/sh

if [[ -z "$CLOUD_ROOT" ]]; then
  echo "ERROR: Environment variable CLOUD_ROOT not found." 1>&2
  exit 1
fi

if [[ -z "$CLOUD_BUILD" ]]; then
  echo "ERROR: Environment variable CLOUD_BUILD not found." 1>&2
  exit 1
fi

mkdir -p $CLOUD_BUILD
cd $CLOUD_BUILD

cmake -B"$CLOUD_BUILD" -H"$CLOUD_ROOT"
make -C "$CLOUD_BUILD" -j8
