package(default_visibility = ["//visibility:public"])

filegroup(
  name = "proto_files",
  srcs = [
    "AnalyzerService.proto",
  ],
)

# cpp library with generated files
load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")
cc_proto_library(
  name = "cc_proto",
  protos = [":proto_files"],
  with_grpc = True,
)

# golang library with generated files
load("@org_pubref_rules_protobuf//go:rules.bzl", "go_proto_library")
go_proto_library(
  name = "go_proto",
  importpath = "go_proto",
  protos = [":proto_files"],
  with_grpc = True,
)
