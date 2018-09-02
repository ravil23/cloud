# Use an official Ubuntu as parent
FROM ubuntu:18.04

# Install any needed packages specified
RUN apt-get update && apt-get upgrade
RUN apt-get install -y cmake clang libc++-dev git wget unzip make

# Install Protobuf
ENV PROTOBUF_VERSION 3.6.1
RUN apt-get install -y autoconf automake libtool g++
RUN cd /tmp && wget https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protobuf-all-${PROTOBUF_VERSION}.zip -O protobuf.zip && unzip protobuf.zip && cd protobuf-${PROTOBUF_VERSION} && ./configure && make -j8 && make install && cd / && rm -rf /tmp/protobuf.zip /tmp/protobuf-${PROTOBUF_VERSION} && ldconfig

# Install GRPC
ENV GRPC_VERSION 1.14.2
RUN apt-get install -y build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev libc-ares-dev libssl-dev google-perftools libgoogle-perftools-dev zlib1g-dev
RUN cd /tmp && wget https://github.com/grpc/grpc/archive/v${GRPC_VERSION}.zip -O grpc.zip && unzip grpc.zip && cd grpc-${GRPC_VERSION} && make -j8 && make install && cd / && rm -rf /tmp/grpc.zip /tmp/grpc-${GRPC_VERSION} && ldconfig

# Install GLOG
ENV GLOG_VERSION 0.3.5
RUN cd /tmp && wget https://github.com/google/glog/archive/v${GLOG_VERSION}.zip -O glog.zip && unzip glog.zip && cd glog-${GLOG_VERSION} && mkdir build && cd build && cmake .. && make -j8 && make install && cd / && rm -rf glog.zip glog-${GLOG_VERSION} && ldconfig

# Install GTEST
ENV GTEST_VERSION 1.8.1
RUN cd /tmp && wget https://github.com/google/googletest/archive/release-${GTEST_VERSION}.zip -O gtest.zip && unzip gtest.zip && cd googletest-release-${GTEST_VERSION} && mkdir build && cd build && cmake .. && make -j8 && make install && cd / && rm -rf gtest.zip googletest-release-${GTEST_VERSION} && ldconfig

# Define environment variable
ENV NAME "Cloud Env"
ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++