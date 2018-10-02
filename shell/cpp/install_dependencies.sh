#!/bin/sh

# Install any needed packages specified
apt-get update && apt-get install -y --no-install-recommends \
        cmake \
        wget \
        unzip \
        make \
        clang

# Install Protobuf
PROTOBUF_VERSION=3.6.1
apt-get update && apt-get install -y --no-install-recommends \
        autoconf \
        automake \
        libtool \
        g++ \
    && cd /tmp \
    && wget --no-check-certificate https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protobuf-all-${PROTOBUF_VERSION}.zip -O protobuf.zip \
    && unzip protobuf.zip \
    && cd protobuf-${PROTOBUF_VERSION} \
    && ./configure \
    && make -j8 \
    && make install \
    && cd / \
    && rm -rf /tmp/protobuf.zip /tmp/protobuf-${PROTOBUF_VERSION} \
    && ldconfig \
    && apt-get remove -y \
        autoconf \
        automake \
        libtool \
        g++ \
    && rm -rf /var/lib/apt/lists/*

# Install GRPC
GRPC_VERSION=1.14.2
apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        autoconf \
        libtool \
        pkg-config \
        libgflags-dev \
        libgtest-dev \
        clang \
        libc++-dev \
        libc-ares-dev \
        libssl-dev \
        google-perftools \
        libgoogle-perftools-dev \
        zlib1g-dev \
    && cd /tmp \
    && wget --no-check-certificate https://github.com/grpc/grpc/archive/v${GRPC_VERSION}.zip -O grpc.zip \
    && unzip grpc.zip && cd grpc-${GRPC_VERSION} \
    && make -j8 \
    && make install \
    && cd / \
    && rm -rf /tmp/grpc.zip /tmp/grpc-${GRPC_VERSION} \
    && ldconfig \
    && apt-get remove -y \
        build-essential \
        autoconf \
        libtool \
        pkg-config \
        libgflags-dev \
        libgtest-dev \
        clang \
        libc++-dev \
        libc-ares-dev \
        libssl-dev \
        google-perftools \
        libgoogle-perftools-dev \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Install GLOG
GLOG_VERSION=0.3.5
cd /tmp \
    && wget --no-check-certificate https://github.com/google/glog/archive/v${GLOG_VERSION}.zip -O glog.zip \
    && unzip glog.zip \
    && cd glog-${GLOG_VERSION} \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j8 \
    && make install \
    && cd / \
    && rm -rf glog.zip glog-${GLOG_VERSION} \
    && ldconfig

# Install GTEST
GTEST_VERSION=1.8.1
cd /tmp \
    && wget --no-check-certificate https://github.com/google/googletest/archive/release-${GTEST_VERSION}.zip -O gtest.zip \
    && unzip gtest.zip \
    && cd googletest-release-${GTEST_VERSION} \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j8 \
    && make install \
    && cd / \
    && rm -rf gtest.zip googletest-release-${GTEST_VERSION} \
    && ldconfig