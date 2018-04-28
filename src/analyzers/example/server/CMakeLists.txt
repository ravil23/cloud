# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/protobuf
  ${CMAKE_BINARY_DIR}/src/server
)

# Set target name.
set(TARGET_NAME example-server)

# Add target (binary file or library) for compiling.
add_executable(${TARGET_NAME}
  main.cpp
)

# Add libraries for linking.
target_link_libraries(${TARGET_NAME}
  protobuf::libprotobuf
  gRPC::grpc++_reflection
  cfa_protobuf
  cfa_grpc
)