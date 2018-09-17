#!/bin/sh

if [ -z "$CLOUD_BIN" ]; then
  echo "ERROR: Environment variable CLOUD_BUILD not found." 1>&2
  exit 1
fi

INSTALL_DIR="$1"

if [ -z "$INSTALL_DIR" ]; then
  echo "ERROR: Install directory required." 1>&2
  exit 1
fi

mkdir -p "$INSTALL_DIR"
cp -r "$CLOUD_BIN"/* "$INSTALL_DIR"