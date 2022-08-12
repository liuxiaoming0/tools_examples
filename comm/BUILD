load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "lib_comm",
  srcs = glob(["*.cc"]),
  hdrs = glob(["*.h"]),
  visibility = [
    "//stl:__pkg__",
    "//gtest_examples:__pkg__",
  ],
)
