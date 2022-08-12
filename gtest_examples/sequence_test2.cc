#include "sequence_test.h"
using testing::Types;
using namespace stl;

// support diffrent types use one case, but type temporary don`t know
namespace {

template<typename T>
class SequenceTest_1 : public testing::Test {
  public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
  protected:
    void SetUp() override {
      gettimeofday(&start_, NULL);
      for(int i = 0; i< 1000000; i++) {
        datas_->Push_batch(i); // 20ms
      }
    }
    void TearDown() override {
      gettimeofday(&end_, NULL);
      usec_ = (end_.tv_sec - start_.tv_sec)*1000000 + (end_.tv_usec - start_.tv_usec);
      cout << COUT_GTEST_MGT << "Spend times = " << usec_ << "us" << ANSI_TXT_DFT << endl;
      delete datas_;
    }

  protected:
    SequenceTest_1() : datas_(new Sequence<T, int>()){}
    
  protected:
    Sequence<T, int>* datas_;
    timeval start_;
    timeval end_;
    long usec_;
};

template<typename T>
class SequenceTest_2 : public SequenceTest_1<T> {};
TYPED_TEST_SUITE_P(SequenceTest_2);

TYPED_TEST_P(SequenceTest_2, test2) {
  ASSERT_TRUE(this->datas_ != nullptr); // only use check ptr
}
TYPED_TEST_P(SequenceTest_2, test2_find_insert) {
  this->datas_->Insert_After(50000, 1000001);
  EXPECT_EQ(1000001, this->datas_->Size());
  EXPECT_TRUE(this->datas_->Size() == 1000001);
}

// support have impl instance define
// 支持有实例后再定义，若不注册，上面的测试用例也不会报错
// 一般用在抽象接口还有实例化时的用例
REGISTER_TYPED_TEST_SUITE_P(SequenceTest_2, test2, test2_find_insert);

typedef Types<vector<int>, deque<int>, list<int>> impls;
INSTANTIATE_TYPED_TEST_SUITE_P(instance,
                               SequenceTest_2,
                               impls);
}