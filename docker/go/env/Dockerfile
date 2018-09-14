# Use an official Ubuntu as parent
FROM ubuntu:18.04

# Install any needed packages specified
ENV GO_VERSION 1.10
RUN apt-get update && apt-get install golang-$GO_VERSION

# Define environment variable
ENV NAME "Cloud Go Env"