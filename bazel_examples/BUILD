load("//bazel_examples:try_rule.bzl", "test_rule")

filegroup(
    name = "bazel_examples_files",
    srcs = glob([
        "*",
        "**/*",
    ]),
    visibility = ["//visibility:public"],
)

test_rule(
    name = "test_rule",
    srcs = [
        "//bazel_examples:bazel_examples_files",
    ],
)
