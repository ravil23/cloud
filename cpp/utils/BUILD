package(default_visibility = ["//cpp:__subpackages__"])

cc_library(
  name = "lexical_cast",
  hdrs = ["lexical_cast.h"],
)

cc_library(
  name = "protobuf_formatter",
  hdrs = ["protobuf_formatter.h"],
)

cc_library(
  name = "protobuf_stream",
  hdrs = ["protobuf_stream.h"],
)

cc_library(
  name = "server_base",
  hdrs = ["server_base.h"],
  deps = [":lexical_cast"],
)
