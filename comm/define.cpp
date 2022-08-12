#include "define.h"

namespace comm {

std::string ToString(std::string& s) {
  return s;
}

std::string ToString(const char* s) {
  std::string tmp = s;
  return tmp;
}

std::string ToString(const int& s) {
  return std::to_string(s);
}

} // namespace name
