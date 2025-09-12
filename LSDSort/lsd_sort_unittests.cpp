#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

#include "LSDSort/lsd_sort.hpp"

class LSDSortTest : public ::testing::TestWithParam<size_t> {};

TEST_P(LSDSortTest, RandomShuffle) {
  std::random_device rand_device;
  std::mt19937 gen(rand_device());

  const size_t kSize = GetParam();
  std::vector<uint64_t> arr(kSize);
  std::vector<uint64_t> res(kSize);
  std::iota(arr.begin(), arr.end(), 0);
  std::shuffle(arr.begin(), arr.end(), gen);

  Aads::LSDSort(arr.begin(), arr.end(), res.begin(), res.end());

  for (size_t i = 0; i < kSize; ++i) {
    EXPECT_EQ(res[i], i);
  }
}

TEST_P(LSDSortTest, RandomShuffleSubarray) {
  std::random_device rand_device;
  std::mt19937 gen(rand_device());

  const size_t kSize = GetParam();
  const size_t kBegin = kSize / 3;
  const size_t kEnd = kSize * 2 / 3;

  std::vector<uint64_t> arr(kSize);
  std::vector<uint64_t> res(kSize);

  std::iota(arr.begin(), arr.end(), 0);
  std::iota(arr.begin() + kBegin, arr.begin() + kEnd, 0);
  std::shuffle(arr.begin() + kBegin, arr.begin() + kEnd, gen);

  Aads::LSDSort(arr.begin() + kBegin, arr.begin() + kEnd, res.begin() + kBegin,
                res.begin() + kEnd);

  for (size_t i = kBegin; i < kEnd; ++i) {
    EXPECT_EQ(res[i], i - kBegin);
  }
}

TEST(LSDSortTest, EmptyArraySort) {
  std::vector<uint64_t> vec;
  std::vector<uint64_t> res;
  Aads::LSDSort(vec.begin(), vec.end(), res.begin(), res.end());
}

INSTANTIATE_TEST_SUITE_P(VaryingSizes, LSDSortTest,
                         ::testing::Values(1, 2, 3, 4, 10, 256, 999, 1234));
