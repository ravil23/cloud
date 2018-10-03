cc_library(
  name = "word_count_analyzer",
  srcs = ["lib/analyzer.cc"],
  hdrs = ["lib/analyzer.h"],
  deps = [
    "//protobuf:cc_proto",
    "//cpp/analyzers:analyzer_interface",
    "@grpc//:grpc++",
   ],
)

cc_binary(
  name = "word_count_analyzer_server",
  srcs = ["server/server.cc"],
  deps = [
    ":word_count_analyzer",
    "//cpp/analyzers:analyzer_service",
    "//cpp/utils:server_base",
  ],
)

# TODO: convert to cc_test
cc_binary(
  name = "word_count_analyzer_test",
  srcs = ["test/analyzer_test.cc"],
  deps = [
    ":word_count_analyzer",
    "@gtest//:gtest_main",
  ],
)
