#include <gtest/gtest.h>
#include "TimSort/timsort.hpp"
#include <vector>
#include <algorithm>

TEST(TimSortTest, SimpleSort) {
  std::vector<int> arr = {5, 2, 8, 1, 9};
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[4], 9);
}

TEST(TimSortTest, AlreadySorted) {
  std::vector<int> arr = {1, 2, 3, 4, 5};
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(TimSortTest, ReverseSorted) {
  std::vector<int> arr = {5, 4, 3, 2, 1};
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(TimSortTest, Duplicates) {
  std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5};
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(TimSortTest, LargeArray) {
  std::vector<int> arr(1000);
  for (int i = 0; i < 1000; ++i) {
    arr[i] = 1000 - i;
  }
  
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[999], 1000);
}

TEST(TimSortTest, SingleElement) {
  std::vector<int> arr = {42};
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_EQ(arr[0], 42);
}

TEST(TimSortTest, TwoElements) {
  std::vector<int> arr = {2, 1};
  Aads::TimSort(arr.begin(), arr.end());
  
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
}
