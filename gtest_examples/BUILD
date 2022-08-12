load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library (
  name = "gtest_lib",
  srcs = [
      # "*.cc",
    ],
  hdrs = glob(["*.h"]),
)

cc_test(
  name = "sequence_test",
  srcs = [
    "sequence_test.cc",
    "sequence_test1.cc",
    "sequence_test2.cc",
  ],
  # linkstatic = 0,
  deps = [
    "//comm:lib_comm", 
    "//stl:stl_lib",
    "//gtest_examples:gtest_lib",
    "@com_google_googletest//:gtest_main",
  ],
)

cc_test(
  name = "abtract_test",
  srcs = [
    "abtract_test.cc",
    "abtract_function_test.cc",
    "combine_test.cc",
  ],
  deps = [
    "//comm:lib_comm", 
    "//stl:stl_lib",
    "//gtest_examples:gtest_lib",
    "@com_google_googletest//:gtest_main",
  ],
)
