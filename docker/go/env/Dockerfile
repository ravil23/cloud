# Use an official Ubuntu as parent
FROM ubuntu:18.04

# Set environment variables
ENV GOROOT="/usr/local/go"
ENV GOPATH="/root/go"
ENV PATH="$PATH:$GOROOT/bin:/$GOPATH/bin"

# Copy installation script
COPY ./go/install_dependencies.sh install_dependencies.sh

# Install any needed packages specified
RUN sh install_dependencies.sh && rm install_dependencies.sh

# Define environment variable
ENV NAME "Cloud Go Env"