load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

package(
  default_visibility = [
    "//visibility:public",
  ],
)

cc_library (
  name = "stl_lib",
  srcs = [
    # "abtract.cc",
    ],
  hdrs = glob(["*.h"]),
)

cc_binary(
  name = "stl_bin",
  srcs = ["main.cc"],
  deps = [
    "//comm:lib_comm", 
    "//stl:stl_lib",
    ],
)