# Use an environment cloud image as parent
FROM cloud-go-env:latest

# Copy the current directory contents into the container at /cloud
COPY . /source

# Build
RUN cd /source \
    && . shell/env.sh \
    && sh go/make_build.sh \
    && sh go/make_test.sh \
    && sh go/make_install.sh /cloud/bin \
    && rm -r /source

# Set the working directory
WORKDIR /cloud

# Define environment variable
ENV NAME "Cloud Go Binaries"

# Run bash when the container launches
CMD ["/bin/bash"]