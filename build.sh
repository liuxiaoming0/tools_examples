#!/bin/bash

bazel clean
# 参考链接：https://bazel.build/rules/performance#hanging

# 1、只生成编译产物
bazel build //stl:stl_bin --verbose_failures

# 2、浏览器查看CPU和内存
PROFILE_PATH=/data/home/danaeliu/samba/c11book/tools_examples/profile
bazel build //stl:stl_bin --verbose_failures --profile=$PROFILE_PATH/stl_profile.gz
# Google Chrome访问chrome://tracing/，加载xxx.gz文件

# 3、生成运行时间百分比
bazel build //stl:stl_bin --verbose_failures --profile=/PROFILE_PATH/stl_prof
bazel analyze-profile ./profile/stl_prof

# 4、内存占用
# 1）设置变量
BAZEL="/data/home/danaeliu/samba/bazel"
STARTUP_FLAGS="--host_jvm_args=-javaagent:${BAZEL}/third_party/allocation_instrumenter/java-allocation-instrumenter-3.3.0.jar --host_jvm_args=-DRULE_MEMORY_TRACKER=1"
# 2）使用内存跟踪
bazel ${STARTUP_FLAGS} build //stl:stl_bin
echo "=========result==========="
# 3) 展示内存占用25M
bazel ${STARTUP_FLAGS} info used-heap-size-after-gc
# 4）展示各规则内存占用
bazel $STARTUP_FLAGS dump --rules
# 5）生成pprof文件
# sudo yum install dump
# echo $STARTUP_FLAGS
bazel ${STARTUP_FLAGS} dump --skylark_memory=$PROFILE_PATH/prof.gz
pprof -text -lines $PROFILE_PATH/prof.gz