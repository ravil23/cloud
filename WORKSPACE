workspace(name = "com_github_ravil23_cloud")

# add grpc
git_repository(
    name = "grpc",
    remote = "https://github.com/grpc/grpc.git",
    tag = "v1.13.1",
    init_submodules = True,
)

# add gtest
git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest.git",
    commit = "bea3d619757e6844a11b4f7c2f85ee05b73abd41",
    init_submodules = True,
)

# add glog
git_repository(
    name = "glog",
    remote = "https://github.com/google/glog.git",
    commit = "8d7a107d68c127f3f494bb7807b796c8c5a97a82",
    init_submodules = True,
)

# add gflags
git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    commit = "c0b1add45fbc40dedd5e820bf38ebc5ce1a61e3d",
    init_submodules = True,
)

# # add go rules
# git_repository(
#     name = "io_bazel_rules_go",
#     remote = "https://github.com/bazelbuild/rules_go.git",
#     commit = "a390e7f7eac912f6e67dc54acf67aa974d05f9c3",
# )
# load("@io_bazel_rules_go//go:def.bzl", "go_rules_dependencies", "go_register_toolchains")
# go_rules_dependencies()
# go_register_toolchains()

# add protobuf and grpc rules
git_repository(
    name = "org_pubref_rules_protobuf",
    remote = "https://github.com/pubref/rules_protobuf.git",
    commit = "5cae42382b620aa1e347ecf30b3e92fd0d97998c",
)

load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cpp_proto_repositories")
cpp_proto_repositories()

# load("@org_pubref_rules_protobuf//go:rules.bzl", "go_proto_repositories")
# go_proto_repositories()
