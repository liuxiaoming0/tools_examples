load("@rules_cc//cc:defs.bzl", "cc_binary") #github.com/bazelbuild/rules_cc
# load("@rules_pkg//pkg:pkg.bzl", "pkg_zip")
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")


# 1、custom rule, use actions.run
def _compile_implementation(ctx):
    # g++ source1 source2 -o xxx.o -c
    for f in ctx.files.srcs:
        output = []
        out = ctx.actions.declare_file(
            "{}.o".format(f.path[:-3])
        )
        print("compiling {} -> {}".format(f, out))

        inputs = [f]
        inputs.extend(ctx.files.hdfs)
        args = ctx.actions.args()
        args.add(f)
        args.add("-o")
        args.add(out)
        args.add("-c")

        output.append(out)

        ctx.actions.run(
            executable = "/usr/bin/g++",
            arguments = [args],
            inputs = inputs,
            outputs = [out],
        )
    return [DefaultInfo(files = depset(output)
    )]

compile = rule(
    implementation = _compile_implementation,
    attrs = {
        "srcs": attr.label_list(
            allow_files = True,
            doc = "input source files",
        ),
        "hdfs": attr.label_list(
            allow_files = True,
            doc = "input header files",
        ),
    },
    executable = False,
    test = False,
)

# 2. custom rule, use label
def _linker_implementation(ctx):
    # g++ xxx.o -o a.out
    args = ctx.actions.args()
    args.add_all(ctx.files.objs)
    args.add("-o")
    args.add(ctx.outputs.out)
    args.add("-B")
    args.add("/usr/bin")

    ctx.actions.run(
        outputs = [ctx.outputs.out],
        inputs = ctx.files.objs,
        executable = "/usr/bin/g++",
        arguments = [args],
    )
    return [DefaultInfo(files = depset([ctx.outputs.out])
    )]

linker = rule(
    implementation = _linker_implementation,
    attrs = {
        "objs": attr.label_list(
            allow_files = True,
            doc = "compiled objects files",
        ),
        "out": attr.output(),
    },
    executable = False,
    test = False,
)

# 3、custom rule
def _zip_archive_implementation(ctx):
    out = ctx.outputs.out
    srcs = ctx.files.binfiles
    # zip xxx.zip source1 source2
    args = ctx.actions.args()
    args.add(out)
    args.add_all(srcs)
    ctx.actions.run(
        executable = "zip",
        arguments = [args],
        inputs = srcs,
        outputs = [out],
    )
    return [DefaultInfo(files = depset([out])
    )]

zip_archive = rule(
    implementation = _zip_archive_implementation,
    attrs = {
        "binfiles": attr.label_list(
            allow_files = True,
            doc = "archive target files",
        ),
        "out": attr.output()
    },
    executable = False,
    test = False,
)

# 4、combine three rules
def cc_binary_custom(name, srcs, hdfs, out):
    complie_target_name = "{}-compile".format(name)
    linker_target_name = "{}-linker".format(name)
    archive_target_name = "{}-archive".format(name)

    compile(
        name = complie_target_name,
        srcs = srcs,
        hdfs = hdfs,
    )

    linker(
        name = linker_target_name,
        # objs = ["//bazel_example:compile"],
        objs = [complie_target_name],
        out = out,
    )

    zip_archive(
        name = name,
        binfiles = [linker_target_name, "BUILD"],
        out = "archive.zip",
    )

def cc_binary_native(name, srcs, hdfs):
    cc_binary_target_name = "{}-binary".format(name)
    cc_binary(
        name = cc_binary_target_name,
        srcs = srcs,
        includes = hdfs,
    )
    pkg_tar(
        name = name,
        srcs = [cc_binary_target_name],
    )
