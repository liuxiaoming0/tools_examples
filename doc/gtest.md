## 一、参考链接

- [googletest官方用例](https://github.com/google/googletest/tree/main/googletest/samples)
- [googletest官方教程](https://google.github.io/googletest/advanced.html)
- [googletest用法总结](https://gohalo.me/post/cpp-gtest-unit-test-usage.html)

## 二、用例简介

### 被测试类为模板类，继承自testing::Test

- sequence_test.cc
  - 功能：基础测试用例，*每种模板类型重复编程*
- sequence_test1.cc
  - 功能：子类作为用例模板参数传递，*先注册好子类才能执行用例*，使用TYPED_TEST
- sequence_test2.cc
  - 功能：子类作为模板参数传递，预设模板抽象类的测试用例，待子类实现时再注册，使用TYPED_TEST_P

### 被测试类为抽象类

- abtract_test.cc
  - 功能：子类通过模板参数工厂函数传递，继承自testing::Test
- abtract_function.cc
  - 功能：子类通过参数传递，继承自TestWithParam\<T\>
  - 功能：支持指定区间范围传参
- combine_test.cc
  - 功能：传递多个参数，支持不同参数组合

## 三、功能简介

### 常用宏

- 1）简单测试

  - TEST
  - 使用：直接写用例
  - 参数：TestSuiteName，用例名称
- 2）相同特性测试

  - TEST_F
  - 使用：
    - 继承testing::Test定义类，SetUp初始化公共特性
    - TEST_F编写用例
  - 参数：TestFixtureName，用例名称
- 3）值参数化测试

  - TEST_P、INSTANTIATE_TEST_SUITE_P
  - 使用：
    - **继承TestWithParam定义类**
    - TEST_P编写用例
    - INSTANTIATE_TEST_SUITE_P实例化绑定参数
  - 参数(TEST_P)：TestFixtureName，用例名称
  - 参数(INSTANTIATE_TEST_SUITE_P)：实例名、TestSuiteName、参数生成器(Range、Values、Combibe)、自定义测试名称（可选）
- 4）值参数化测试（先实例化类型参数）

  - TYPED_TEST_SUITE、TYPED_TEST
  - 使用：
    - **继承自testing::Test定义类**
    - TYPED_TEST_SUITE追加类型参数化
    - TYPED_TEST编写用例
  - 参数(TYPED_TEST_SUITE)：TestFixtureName，继承自testing::Types的类型列表
  - 参数(TYPED_TEST)：TestSuiteName，用例名称
- 5）值参数化测试 (用具类支持延迟实例化类型参数)

  - TYPED_TEST_SUITE_P、TYPED_TEST_P、REGISTER_TYPED_TEST_SUITE_P、INSTANTIATE_TYPED_TEST_SUITE_P
  - 使用：
    - **继承自testing::Test定义类**
    - TYPED_TEST_SUITE_P传入模板类
    - TYPED_TEST_P编写用例
    - REGISTER_TYPED_TEST_SUITE_P注册模板类的用例名称
    - INSTANTIATE_TYPED_TEST_SUITE_P实例化参数类型
  - 参数(TYPED_TEST_SUITE_P)：模板类
  - 参数(TYPED_TEST_P): 模板类，用例名称
  - 参数(REGISTER_TYPED_TEST_SUITE_P)：模板类、全部用例名称
  - 参数(INSTANTIATE_TYPED_TEST_SUITE_P): 实例名，模板类，继承自testing::Types的类型参数
- 6）测试私有成员

  - FRIEND_TEST

### 常用类和函数功能

- testing::AssertionResult
  - 存储断言不成功的失败信息
- testing::Environment
  - 全局测试环境，SetUp(),TearDown()
- testing::Test
  - 所有测试都继承自的抽象类，SetUpTestSuite(), TearDownTestSuite()
- testing::TestWithParam\<T\>
  - 测试参数
- TestSuite
  - 测试套件，TestSuite::name(),testing::type_param()
- testing::TestInfo
  - 测试信息
- testing::TestParamInfo\<T\>
  - 值参数化，T是参数类型
- testing::TestEventListener
  - 事件监听器，支持在测试迭代开始前等执行某事件
- testing::TestResult
  - 测试结果信息
- testing::TimeInmillis
  - 毫秒为单位时间整数
- testing::Types\<T...\>
  - 功能：类型列表
- testing::InitGoogleTest
  - 初始化
