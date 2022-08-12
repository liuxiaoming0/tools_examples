#pragma once

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm> // find()
#include "../comm/define.h"
using namespace std;

namespace stl{

template<typename T, typename V>
class Sequence {
  public:
    Sequence() = default;
    // 新增数据
    void Push_batch(const V& v) { // 构造->移动拷贝/拷贝构造
      container_.push_back(v);
    }
    void Emplace_batch(const V& v) { // 构造
      container_.emplace_back(v);
    }

    // 查找指定元素后新增
    void Insert_After(const V& v1, const V& v2) {
      container_.insert(find(container_.cbegin(), container_.cend(), v1), v2);
    }

    // 工具类
    void Print() {
      for(const auto &it: container_)
        printf("value=%s\n", comm::ToString(it));
    }
    int Size() {
      return static_cast<int>(container_.size());
    }
  private:
    T container_;
};
}