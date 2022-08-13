#!/bin/bash

export GTEST_COLOR=true
source ~/.bashrc

bazel clean
# bazel run gtest_examples:sequence_test --verbose_failures
bazel run gtest_examples:abtract_test
# bazel coverage gtest_examples:abtract_test
# genhtml --output-directory coverage-report bazel-testlogs/gtest_examples/abtract_test/coverage.dat

# 注：result fail
# bazel test --test_output=all --color=yes gtest_examples:abtract_test
