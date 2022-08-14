def _test_rule_implementation(ctx):
    srcs = ctx.files.srcs
    print(srcs)
    return [DefaultInfo(files = depset([])
    )]

test_rule = rule(
    implementation = _test_rule_implementation,
    attrs = {
        "srcs": attr.label_list(
            allow_files = True,
            doc = "input source files",
        ),
    },
    executable = False,
    test = False,

    native.# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
    cc_binary(
        name = "rule unique name",
        srcs = ["source files"],
        copts = [],
        deps = ["libraries to be linked"],
    )
)

