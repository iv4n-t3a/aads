#include <random>

#pragma once

namespace Aads {

namespace Util {

class RandomGenerator {
 public:
  RandomGenerator() {
    std::random_device rd;
    rand_ = std::mt19937(rd());
  }

  size_t operator()() { return rand_(); }

 private:
  std::mt19937 rand_;
};

}  // namespace Util

}  // namespace Aads
