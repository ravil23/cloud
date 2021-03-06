cmake_minimum_required(VERSION 3.10.2)

# ---[ Project
project(cloud CXX)
set(PROJECT_VERSION 1.0.1)

# ---[ Install path
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# ---[ Using cmake scripts and modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# ---[ Dependencies
include(cmake/depends.cmake)

# ---[ Build flags
include(cmake/build.cmake)

# ---[ Additional headers search path
include_directories(
  ${PROJECT_SOURCE_DIR}/cpp/include
)

# ---[ Additional libraries search path
link_directories(
  ${PROJECT_BINARY_DIR}/lib
)

# ---[ Test
enable_testing()

# ---[ Subdirectories
add_subdirectory(protobuf)
add_subdirectory(cpp)