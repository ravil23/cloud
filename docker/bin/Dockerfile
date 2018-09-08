# Use an environment cloud image as parent
FROM cloud-env:latest

# Install any needed packages for build
RUN apt-get update && apt-get install -y --no-install-recommends \
        cmake \
        clang \
        make
ENV CC /usr/bin/clang
ENV CXX /usr/bin/clang++

# Copy the current directory contents into the container at /cloud
COPY . /tmp/source

# Build
RUN cd /tmp/source \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j8 \
    && ctest \
    && mkdir /cloud \
    && mv bin /cloud/bin \
    && mv lib /cloud/lib \
    && cd / \
    && rm -r /tmp/source

# Set the working directory
WORKDIR /cloud

# Define environment variable
ENV NAME "Cloud Binaries"

# Run bash when the container launches
CMD ["/bin/bash"]