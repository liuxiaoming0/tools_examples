load("//bazel_examples:theory_rule.bzl", "printer", "printer_with_label", "zip_cmd")
# load("@c_structure_proj//bazel_examples:theory_rule.bzl", "printer")
load("//bazel_examples:simulate_compile_rule.bzl", "cc_binary_custom", "cc_binary_native")

# 1、simple rule
printer(
  name = "printer",
  number = 5,
)

# 2、simple rule, use label、file、provider
printer_with_label(
  name = "printer_with_label",
  mylabel = "//bazel_examples:printer",
  outfile = "start2.txt",
)

# 3、custom rule, use actions.run
zip_cmd(
  name = "zip_cmd",
  sources = ["theory_rule.bzl", "BUILD"],
  out = "out.zip",
)

genrule(
  name = "zip_cmd_genrule",
  srcs = ["theory_rule.bzl", "BUILD"],
  outs = ["out1.zip"],
  cmd = "zip $(OUTS) $(SRCS)",
)

# 自定义编译规则, 编译->链接->打包
cc_binary_custom(
  name = "cc_binary_custom",
  srcs = ["main.cc"],
  hdfs = [],
  out = "a.out",
)

cc_binary_native(
  name = "cc_binary_native",
  srcs = ["main.cc"],
  hdfs = [],
)