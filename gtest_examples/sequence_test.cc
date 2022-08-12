#include "sequence_test.h"
using namespace stl;

namespace {

class SequenceTest : public testing::Test {
  public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
  protected:
    void SetUp() override {
      gettimeofday(&start_, NULL);
      for(int i = 0; i< 1000000; i++) {
        v_->Push_batch(i); // 20ms
        d_->Push_batch(i); // 20ms
        l_->Push_batch(i); // 140ms
      }
    }
    void TearDown() override {
      gettimeofday(&end_, NULL);
      usec_ = (end_.tv_sec - start_.tv_sec)*1000000 + (end_.tv_usec - start_.tv_usec);
      cout << COUT_GTEST_MGT << "Spend times = " << usec_ << "us" << ANSI_TXT_DFT << endl;
      delete v_;
      delete d_;
      delete l_;
      v_ = nullptr;
      d_ = nullptr;
      l_ = nullptr;
    }

  protected:
    SequenceTest() {
      v_ = new Sequence<vector<int>, int>();
      d_ = new Sequence<deque<int>, int>();
      l_ = new Sequence<list<int>, int>();
    }
    
  protected:
    Sequence<vector<int>, int>* v_;
    Sequence<deque<int>, int>* d_;
    Sequence<list<int>, int>* l_;

    timeval start_;
    timeval end_;
    long usec_;
};

TEST_F(SequenceTest, test_vector) {
  ASSERT_TRUE(v_ != nullptr);
  v_->Insert_After(50000, 1000001);
  EXPECT_EQ(1000001, v_->Size());
}

TEST_F(SequenceTest, test_deque) {
  ASSERT_TRUE(d_ != nullptr);
  d_->Insert_After(50000, 1000001);
  EXPECT_EQ(1000001, d_->Size());
}

TEST_F(SequenceTest, test_list) {
  ASSERT_TRUE(l_ != nullptr);
  l_->Insert_After(50000, 1000001);
  EXPECT_EQ(1000001, l_->Size());
}

}