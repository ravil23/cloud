# Use an official Golang as parent
FROM golang:1.11.0

# Copy installation script
COPY ./go/install_dependencies.sh install_dependencies.sh

# Install any needed packages specified
RUN sh install_dependencies.sh && rm install_dependencies.sh

# Define environment variable
ENV NAME "Cloud Go Env"