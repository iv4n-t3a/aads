#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

#include "QuickSort/quicksort.hpp"

class QuickSortTest : public ::testing::TestWithParam<size_t> {};

TEST_P(QuickSortTest, RandomShuffle) {
  std::random_device rand_device;
  std::mt19937 gen(rand_device());

  const size_t kSize = GetParam();
  std::vector<int> arr(kSize);
  std::iota(arr.begin(), arr.end(), 0);
  std::shuffle(arr.begin(), arr.end(), gen);

  Aads::QuickSort(arr.begin(), arr.end());

  for (size_t i = 0; i < kSize; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}

TEST_P(QuickSortTest, RandomShuffleSubarray) {
  std::random_device rand_device;
  std::mt19937 gen(rand_device());

  const size_t kSize = GetParam();
  const size_t kBegin = kSize / 3;
  const size_t kEnd = kSize * 2 / 3;

  std::vector<int> arr(kSize);
  std::iota(arr.begin(), arr.end(), 0);
  std::iota(arr.begin() + kBegin, arr.begin() + kEnd, 0);
  std::shuffle(arr.begin() + kBegin, arr.begin() + kEnd, gen);

  Aads::QuickSort(arr.begin() + kBegin, arr.begin() + kEnd);

  for (size_t i = kBegin; i < kEnd; ++i) {
    EXPECT_EQ(arr[i], i - kBegin);
  }
}

TEST(QuickSortTest, EmptyArraySort) {
  std::vector<int> vec;
  Aads::QuickSort(vec.begin(), vec.end());
}

INSTANTIATE_TEST_SUITE_P(VaryingSizes, QuickSortTest,
                         ::testing::Values(1, 2, 3, 4, 10, 256, 999, 1234));
