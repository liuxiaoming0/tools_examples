#!/bin/bash

bazel clean
# bazel build //bazel_examples:all

# bazel build //bazel_examples:printer
# bazel build //bazel_examples:printer_with_label
# bazel build //bazel_examples:zip_cmd
# bazel build //bazel_examples:zip_cmd_genrule
# bazel build //bazel_examples:cc_binary_native

bazel build //bazel_examples:test_rule