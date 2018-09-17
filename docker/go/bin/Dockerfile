# Use an environment cloud image as parent
FROM cloud-go-env:latest

# Copy the current directory contents into the container at /cloud
COPY . /tmp/source

# Set environment variables
ENV CLOUD_ROOT  /tmp/source
ENV CLOUD_BUILD /tmp/source/build
ENV CLOUD_BIN   /tmp/source/bin
ENV CLOUD_LIB   /tmp/source/lib

# Build
RUN cd /tmp/source \
    && sh go/make_build.sh \
    && sh go/make_test.sh
    # && rm -r /tmp/source

# Set the working directory
WORKDIR /cloud

# Define environment variable
ENV NAME "Cloud Go Binaries"

# Run bash when the container launches
CMD ["/bin/bash"]