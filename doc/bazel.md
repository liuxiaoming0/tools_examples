### 一、前言

> bazel和cmake类似，同样适用大型、混合语言、多平台、非时间戳增量构建项目。

功能如下：

- 使用内置规则可完成简单的编译生成可执行文件。
- 也支持自定义规则，对输入参数实现特定操作后输出，可将不同规则集成到函数中简化调用
- 使用工具链指定平台、工具gcc、ld、ar路径

#### 1.1 参考文章

官方文档

- [Bazel Repositorires](https://github.com/orgs/bazelbuild/repositories?type=all)
  - [bazel官方用例](https://github.com/bazelbuild/examples)
  - [bazelbuild/platforms](https://github.com/bazelbuild/platforms)
- [bazel官方教程](https://bazel.build/)
  - [使用bazel实现代码覆盖率](https://bazel.build/docs/coverage)
  - [bazel教程：配置C++工具链例子](https://bazel.build/tutorials/cc-toolchain-config#before_you_begin)、[C++工具链配置API](https://bazel.build/docs/cc-toolchain-config-reference)
  - [bazel命令](https://bazel.build/reference/command-line-reference)（bazel build/run/test/....）
  - [使用外部依赖项](https://bazel.build/docs/external)（、 [git_repository](https://bazel.build/rules/lib/repo/git)、[http_repository](https://bazel.build/rules/lib/repo/http)）
  - [depset、ctx/actions.args()、性能剖析](https://bazel.build/rules/performance#performance-profiling)

博文

- [视频教程bazel使用-bili](https://www.bilibili.com/video/BV1SL4y177ww/?spm_id_from=autoNext&vd_source=bf2d65f16e873e96e7770900fac79f73)
- [bazel 自定义规则入门](https://zhuanlan.zhihu.com/p/462395365)
- [知乎系列bazel学习笔记](https://zhuanlan.zhihu.com/p/430975467)
- [自定义规则实现多静态库合并成](https://blog.csdn.net/FreeApe/article/details/108680891)
- [对官网C++工具链实例改造](https://cloud.tencent.com/developer/article/1677379)

### 二、安装

#### 2.1 centos安装bazel5.2.0

```
$ sudo su
$ wget https://github.com/bazelbuild/bazel/releases/download/5.2.0/bazel-5.2.0-installer-linux-x86_64.sh .
$ chmod +x ./bazel-5.2.0-installer-linux-x86_64.sh
$ ./bazel-5.2.0-installer-linux-x86_64.sh
$ bazel version
```

#### 2.2 安装lcov

`yum install lcov`

### 三、bazel用法

#### 3.1 名词解释 [链接](https://bazel.build/reference/glossary)

- ***workspace***：对应一个工程
- ***packages***：包含BUILD的目录，不包括有BUILD的子目录
- ***rule***: 内置规则和自定义规则
- ***target***：调用rule生成的构建目标，target_name

#### 3.2 文件说明

- ***WORKSPACE*** : 可为空，包含用于从网络或本地文件系统中提取其他依赖项的外部代码库声明
- ***.bazelrc***：命令默认指定参数
- ***BUILD***：load声明rule --> 调用rule --> 生成targets
- ***.bzl***：编写自定义rule

#### 3.3 基本语法

- load声明规则

  - 远程规则:  `@workspace//package/path/:target_name`
  - 本地规则:  `//package/path/:target_name`
    - package所有targets:  `//package/...`
- 设置规则可见性

  ```
  package(
    default_visibility = [
      "//visibility:public",  # 全部workspace完全公开
      "//visibility:private", # package内公开
      "@my_repo//foo/bar:__pkg__", # package内所有targets
      "//foo/bar:__subpackages__", # package及其子目录package的所有targets
    ],
  )
  ```
- 内置规则 [链接](https://bazel.build/reference/be/c-cpp)

  - cc_binary: 可执行文件
  - cc_library: 动态库、静态库
  - cc_import: 导入预编译的c库
  - cc_proto_library:  proto文件生成c++代码
  - cc_test：c测试用例
  - cc_toolchain: c++工具链
  - cc_toolchain_suite: 工具链集合
  - platform：系统和硬件组合
    ```
    platform(
        name = "linux_x86",
        constraint_values = [
            "@platforms//os:linux",
            "@platforms//cpu:x86_64",
        ],
    )
    ```
- 自定义规则

  ```
  def _impl(ctx):
      ctx.actions.run(
          inputs = []
          outputs =  
          arguments = [] 
          executable = 
      )

  cunstorm_rule=rule(
      implementation = _impl,
      attrs = {
          "inputs": attr.label_list(allow_files = True), # 输入
          "out": attr.output(mandatory = True),          # 输出
      },
  )
  ```
- 函数功能

  - ctx.actions.run: 运行可执行文件
  - ctx.actions.run_shell: 运行脚本命令
  - ctx.actions.write: 写文件
  - ctx.actions.declare_file: 创建文件
  - ctx.actions.expand_template: 从模板创建文件
- 其他
  `$ gcc -shared -fPIC -Wl,--whole-archive libA.a libB.a libC.a  -o libcombined.so `

  query、remote_execution、config_setting

### 四、问题

- bazel run pass, but bazel test fail ? [bazel issues](https://github.com/bazelbuild/bazel/issues/15687)
  bazel test exitCode, `echo $? , 判断不为0则失败`
