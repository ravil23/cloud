# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib
  ${CMAKE_BINARY_DIR}/protobuf
  ${GTEST_INCLUDE_DIR}
)

# Set target name.
set(TARGET_NAME word_count_analyzer-test)

# Add target (binary file or library) for compiling.
add_executable(${TARGET_NAME} 
  test_word_count_analyzer.cpp
)

# Add libraries for linking.
target_link_libraries(${TARGET_NAME}
  ${GTEST_LIBRARY}
  ${GTEST_MAIN_LIBRARY}
  protobuf::libprotobuf
  grpc::grpc++_reflection
  cloud_protobuf
  word_count_analyzer
)

# Add test.
gtest_discover_tests(${TARGET_NAME})