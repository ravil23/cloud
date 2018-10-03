#!/bin/sh

apt-get update
apt-get install -y pkg-config zip g++ zlib1g-dev unzip python wget
wget https://github.com/bazelbuild/bazel/releases/download/0.17.2/bazel-0.17.2-installer-linux-x86_64.sh -O install_bazel.sh
chmod +x install_bazel.sh
./install_bazel.sh
rm -f install_bazel.sh
