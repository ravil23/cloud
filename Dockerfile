# Use an official Ubuntu as parent
FROM ubuntu:16.04

# Export env settings
ENV LANG en_US.UTF-8

# Copy the current directory contents into the container at /cloud
ADD . /cloud

# Install any needed packages specified
RUN apt-get update -y && apt-get install -y cmake protobuf-compiler

# Build
RUN mkdir /cloud/build && cd /cloud/build && cmake .. && make all -j20

# Set the working directory
WORKDIR /cloud/build

# Run tests
RUN ctest

# Define environment variable
ENV NAME "Cloud"

# Run bash when the container launches
CMD ["/bin/bash"]