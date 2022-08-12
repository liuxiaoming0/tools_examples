#include "../comm/test.h"
#include "abtract.h"
#include "../comm/define.h"
#include <tuple>
#include <cstring>
#include <cstdio>

using namespace stl;
using namespace comm;
using ::testing::Bool;
using ::testing::Combine;
using ::testing::TestWithParam;
using ::testing::Values;

namespace {

class ComplexShow {
  public:
    ComplexShow(const bool v, const int v1, const int v2) : v_(v) {
      if (v_) {
        imp1_ = new Impl1();
        imp1_->SetData(10);
      } else {
        imp3_ = new Impl3(v1, v2);
        imp3_->SetData(20);
      }
    }
    ~ComplexShow() {
      RELEASE_PTR(imp1_);
      RELEASE_PTR(imp3_);
    }
    int GetData() {
      if (v_) return imp1_->GetData();
      else return imp3_->GetData();
    }
  private:
    Impl1* imp1_;
    Impl3* imp3_;
    bool v_;
};

enum class TYPES { TYPE1 = 0, TYPE2 = 1 };
class CombineTest : public testing::TestWithParam<std::tuple<TYPES, int, int>> {
  protected:
    void SetUp() override {
      TYPES v_;
      int v1_;
      int v2_;
      std::tie(v_, v1_, v2_) = GetParam();
      show_ = new ComplexShow(static_cast<bool>(v_), v1_, v2_);
    }
    void TearDown() override {
      RELEASE_PTR(show_);
    }
  protected:
    ComplexShow* show_;
};

TEST_P(CombineTest, testData) {
  // std::cout << show_->GetData() << std::endl;
  // std::cout << 0 << std::endl;
  // EXPECT_EQ(25, show_->GetData());
}

INSTANTIATE_TEST_SUITE_P(
          instance, CombineTest, 
          testing::Combine(
            testing::Values(TYPES::TYPE1, TYPES::TYPE2),
            testing::Values(1,2),
            testing::Values(3,4)
          )/*,
          [](const testing::TestParamInfo<CombineTest::ParamType>& info) {
            std::string name = (std::get<0>(info.param) == TYPES::TYPE1) ? "type_1" : "type_2";
            name += std::get<1>(info.param);
            // std::string name = absl::StrCat(
            //   std::get<0>(info.param) == TYPES::TYPE1 ? "type1" : "type2",
            //   std::get<1>(info.param));
            // absl::c_replace_if(name, [](char c){return !std::iswalnum(c);}, '_');
            return name;
          }*/);
}