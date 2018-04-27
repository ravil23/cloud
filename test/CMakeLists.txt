# Add current pathes for search header files.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_PROTO_INCLUDE}
  ${CMAKE_SOURCE_DIR}/src
)

# Set target name.
set(TARGET_NAME main-test)

# Add target (binary file or library) for compiling.
add_executable(${TARGET_NAME} 
  test_main.cpp
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# Add libraries for linking.
target_link_libraries(${TARGET_NAME}
  ${PROJECT_LINKER_LIBS}
  ${PROJECT_PROTO_LIBS}
)

# Add test.
add_test(NAME Main COMMAND ${TARGET_NAME})
