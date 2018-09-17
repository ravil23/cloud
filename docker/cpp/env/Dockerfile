# Use an official Ubuntu as parent
FROM ubuntu:18.04

# Copy installation script
COPY ./cpp/install_dependencies.sh install_dependencies.sh

# Install any needed packages specified
RUN sh install_dependencies.sh && rm install_dependencies.sh

# Define environment variable
ENV NAME "Cloud Env"