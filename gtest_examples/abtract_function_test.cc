#include "../comm/test.h"
#include "abtract.h"
using testing::TestWithParam;
using testing::Values;
using namespace stl;

namespace {

typedef AbtractShow* CreateFunc();

AbtractShow* createImpl1() {
  return new Impl1();
}

template<int a, int b>
AbtractShow* createImpl3() {
  return new Impl3(a, b);
}

// 通过将函数作为参数，对抽象类型的不同实例对象测试
class AbtractShowTest : public TestWithParam<CreateFunc*> {
  public:
    ~AbtractShowTest() override { delete data_;}
  // protected:
    void SetUp() override {
      data_ = (*GetParam())();
      data_->SetData(10);
    }
    void TearDown() override {
      delete data_;
      data_ = nullptr;
    }
  protected:
   AbtractShow* data_;
};

TEST_P(AbtractShowTest, setValue) {
  // 无法判断使用的类型
  // EXPECT_EQ(10, data_->GetData());
}

INSTANTIATE_TEST_SUITE_P(instance,
                               AbtractShowTest,
                               Values(&createImpl1, &createImpl3<100, 200>));

// 通过指定区间传参数
class AbtractShowTest1 : public TestWithParam<int> {
  public:
    ~AbtractShowTest1() override { delete data_;}
  // protected:
    void SetUp() override {
      data_ = new Impl3(100, GetParam());
      data_->SetData(10);
    }
    void TearDown() override {
      delete data_;
      data_ = nullptr;
    }
  protected:
   AbtractShow* data_;
};

TEST_P(AbtractShowTest1, setValue) {
  EXPECT_EQ(110+GetParam(), data_->GetData());
}

// 固定值
// INSTANTIATE_TEST_SUITE_P(instance1,
//                                AbtractShowTest1, 
//                                Values(100, 200));

// 区间值
INSTANTIATE_TEST_SUITE_P(instance1,
                               AbtractShowTest1, testing::Range(1, 10),
                               testing::PrintToStringParamName());
                    
}
