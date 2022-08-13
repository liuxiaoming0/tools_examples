#!/bin/bash

bazel clean

bazel build //stl:stl_bin --verbose_failures
