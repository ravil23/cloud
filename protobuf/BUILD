package(default_visibility = ["//visibility:public"])

filegroup(
    name = "protos",
    srcs = [
        "AnalyzerService.proto",
    ],
)

# cpp library with generated files
load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")
cc_proto_library(
  name = "proto_cc",
  protos = [":protos"],
  with_grpc = True,
)

# golang library with generated files
load("@org_pubref_rules_protobuf//go:rules.bzl", "go_proto_library")
go_proto_library(
  name = "proto_go",
  importpath = "proto_go",
  protos = [":protos"],
  with_grpc = True,
)
