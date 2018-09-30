# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/protobuf
)

# Set target name.
set(TARGET_NAME analyzer-client)

# Add target (binary file or library) for compiling.
add_executable(${TARGET_NAME}
  main.cpp
)

# Add libraries for linking.
target_link_libraries(${TARGET_NAME}
  protobuf::libprotobuf
  grpc::grpc++_reflection
  glog::glog
  cloud_protobuf
  cloud_grpc
)