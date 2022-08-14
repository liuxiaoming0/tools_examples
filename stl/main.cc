#include "../comm/define.h"
#include <stdio.h>
#include "sequence.h"

int main () {
  printf("test = %d\n", comm::MAX_LONG);
  
  stl::Sequence<std::vector<int>, int> s;
  for(int i = 0; i< 1000000; i++) {
    s.Push_batch(i); // 20ms
  }
}
