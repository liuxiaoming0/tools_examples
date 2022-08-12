#include "sequence_test.h"
using testing::Types;
using namespace stl;

// support diffrent types use one case
namespace {

template<typename T>
class SequenceTest1 : public testing::Test {
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
    SequenceTest1() : datas_(new Sequence<T, int>()){}
    
  protected:
    Sequence<T, int>* datas_;
    timeval start_;
    timeval end_;
    long usec_;
};

// must define in advance
typedef Types<vector<int>, deque<int>, list<int>> Implementations;
TYPED_TEST_SUITE(SequenceTest1, Implementations);


TYPED_TEST(SequenceTest1, test_find_insert) {
  this->datas_->Insert_After(50000, 1000001);
  ASSERT_TRUE(this->datas_ != nullptr); // only use check ptr
  EXPECT_EQ(1000001, this->datas_->Size());
  EXPECT_TRUE(this->datas_->Size() == 1000001);
}

}