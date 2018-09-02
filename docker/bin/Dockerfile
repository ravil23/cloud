# Use an environment cloud image as parent
FROM cloud-env:latest

# Export env settings
ENV LANG en_US.UTF-8

# Copy the current directory contents into the container at /cloud
COPY . /tmp/source

# Build
RUN cd /tmp/source && mkdir build && cd build && cmake .. && make -j8 && ctest && mkdir /cloud && mv bin /cloud/bin && mv lib /cloud/lib && cd / && rm -r /tmp/source

# Set the working directory
WORKDIR /cloud

# Define environment variable
ENV NAME "Cloud Binaries"

# Run bash when the container launches
CMD ["/bin/bash"]