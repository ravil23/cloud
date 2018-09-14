# Use an environment cloud image as parent
FROM cloud-cpp-env:latest

# Copy the current directory contents into the container at /cloud
COPY . /tmp/source

# Build
RUN cd /tmp/source \
    && source shell/environments.sh \
    && sh cpp/make_build.sh \
    && sh cpp/make_test.sh \
    && sh cpp/make_install.sh \
    && cd / \
    && rm -r /tmp/source

# Set the working directory
WORKDIR /cloud

# Define environment variable
ENV NAME "Cloud C++ Binaries"

# Run bash when the container launches
CMD ["/bin/bash"]