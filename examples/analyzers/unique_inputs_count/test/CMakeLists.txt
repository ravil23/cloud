# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/protobuf
  ${CMAKE_CURRENT_SOURCE_DIR}/../lib
  ${GTEST_INCLUDE_DIR}
)

# Set target name.
set(TARGET_NAME unique_inputs_counter-test)

# Add target (binary file or library) for compiling.
add_executable(${TARGET_NAME} 
  test_unique_inputs_counter.cpp
)

# Add libraries for linking.
target_link_libraries(${TARGET_NAME}
  ${GTEST_LIBRARY}
  ${GTEST_MAIN_LIBRARY}
  protobuf::libprotobuf
  cloud_protobuf
  unique_inputs_counter
)

# Add test.
gtest_add_tests(${TARGET_NAME} "" AUTO)