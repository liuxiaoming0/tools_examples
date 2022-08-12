#pragma once
#include <string>

namespace comm{

#define RELEASE_PTR(p)        \
  if (p != nullptr) delete p; \
  p = nullptr;

static int MAX_LONG = 256;

std::string ToString(std::string& s);

std::string ToString(const char* s);

std::string ToString(const int& s);

}