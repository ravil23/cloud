# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/protobuf
  ${CMAKE_BINARY_DIR}/src/server
)

# Set target name.
set(TARGET_NAME word_count_analyzer)

# Add target (binary file or library) for compiling.
add_library(${TARGET_NAME} STATIC
  word_count_analyzer.cpp
)

# Add libraries for linking.
target_link_libraries(${TARGET_NAME}
  protobuf::libprotobuf
  cloud_protobuf
)