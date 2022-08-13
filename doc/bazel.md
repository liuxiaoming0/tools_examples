[https://zhuanlan.zhihu.com/p/462395365](https://zhuanlan.zhihu.com/p/462395365)

[https://zhuanlan.zhihu.com/p/421489117](https://zhuanlan.zhihu.com/p/421489117)

[https://blog.csdn.net/FreeApe/article/details/108680891](https://blog.csdn.net/FreeApe/article/details/108680891)

视频教程：[https://www.bilibili.com/video/BV1SL4y177ww/?spm_id_from=autoNext&amp;vd_source=bf2d65f16e873e96e7770900fac79f73](https://www.bilibili.com/video/BV1SL4y177ww/?spm_id_from=autoNext&vd_source=bf2d65f16e873e96e7770900fac79f73)

知乎系列：https://zhuanlan.zhihu.com/p/430975467

### centos安装bazel5.2.0

```
$ sudo su
$ wget https://github.com/bazelbuild/bazel/releases/download/5.2.0/bazel-5.2.0-installer-linux-x86_64.sh .
$ chmod +x ./bazel-5.2.0-installer-linux-x86_64.sh
$ ./bazel-5.2.0-installer-linux-x86_64.sh
$ bazel version
```

### 安装lcov

`yum install lcov`

### 问题

- bazel run pass, but bazel test fail ? [bazel issues](https://github.com/bazelbuild/bazel/issues/15687)
  bazel test exitCode, `echo $?`
