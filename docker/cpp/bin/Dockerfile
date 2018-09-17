# Use an environment cloud image as parent
FROM cloud-cpp-env:latest

# Copy the current directory contents into the container at /cloud
COPY . /source

# Build
RUN cd /source \
    && . shell/env.sh \
    && sh cpp/make_build.sh \
    && sh cpp/make_test.sh \
    && sh cpp/make_install.sh /cloud/bin \
    && rm -r /source

# Set the working directory
WORKDIR /cloud

# Define environment variable
ENV NAME "Cloud C++ Binaries"

# Run bash when the container launches
CMD ["/bin/bash"]