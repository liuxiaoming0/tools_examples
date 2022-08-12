#include "../comm/test.h"
#include "abtract.h"
using testing::Types;
using namespace stl;

// 通过模板，对抽象类型的不同实例对象测试

namespace {

// 抽象类型工厂，用于生产实例对象
template<typename T>
AbtractShow* CreateImpl();

template<>
AbtractShow* CreateImpl<Impl1>() {
  return new Impl1;
}

template<>
AbtractShow* CreateImpl<Impl2>() {
  return new Impl2;
}

template<typename T>
class AbtractShowTest : public testing::Test {
  protected:
    AbtractShowTest() : data_(CreateImpl<T>()){}
    void SetUp() override {
      data_->SetData(10);
    }
    void TearDown() override {
      delete data_;
    }
  protected:
   AbtractShow* data_;
};

template<typename T>
class AbtractShowTest2 : public AbtractShowTest<T>{};

TYPED_TEST_SUITE_P(AbtractShowTest2);

TYPED_TEST_P(AbtractShowTest2, setValue) {
  // 不同的子类，值不同
  // EXPECT_EQ(10, this->data_->GetData());
}

REGISTER_TYPED_TEST_SUITE_P(AbtractShowTest2, setValue);

typedef Types<Impl1, Impl2> impls;
INSTANTIATE_TYPED_TEST_SUITE_P(instance,
                               AbtractShowTest2,
                               impls);
}
