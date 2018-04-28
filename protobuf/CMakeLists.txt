# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# List of proto files.
set(PROTO_FILES
  analyzer_service.proto
)

# Generate code from proto files.
protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${CMAKE_CURRENT_BINARY_DIR} ${PROTO_FILES})
grpc_generate_cpp(GRPC_SOURCES GRPC_HEADERS ${CMAKE_CURRENT_BINARY_DIR} ${PROTO_FILES})

# Add library for generated Protobufs.
set(PROJECT_PROTO_LIB cfa_protobuf)
add_library(${PROJECT_PROTO_LIB} STATIC
  ${PROTO_SOURCES}
)

# Add library for generated gRPC services.
set(PROJECT_GRPC_LIB cfa_grpc)
add_library(${PROJECT_GRPC_LIB} STATIC
  ${GRPC_SOURCES}
)

# Add libraries for linking.
target_link_libraries(${PROJECT_GRPC_LIB}
  ${PROJECT_PROTO_LIB}
)