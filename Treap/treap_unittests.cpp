#include <gtest/gtest.h>

#include <algorithm>

#include "Treap/treap.hpp"

TEST(TreapTest, InsertSimple) {
  Aads::Treap<int> treap;
  std::vector<int> order = {0, 1, 0, 3, 2};

  for (size_t i = 0; i < order.size(); ++i) {
    treap.Insert(order[i], i);
  }

  ASSERT_EQ(treap[0], 2);
  ASSERT_EQ(treap[1], 0);
  ASSERT_EQ(treap[2], 4);
  ASSERT_EQ(treap[3], 1);
  ASSERT_EQ(treap[4], 3);
}

TEST(TreapTest, InsertStupidStress) {
  const int kSize = 1234;

  Aads::Treap<int> treap;

  std::vector<int> elements(kSize);
  std::iota(elements.begin(), elements.end(), 0);
  std::random_device rand_device;
  std::mt19937 gen(rand_device());
  std::shuffle(elements.begin(), elements.end(), gen);

  for (size_t i = 0; i < kSize; ++i) {
    treap.Insert(i, elements[i]);
  }
  for (size_t i = 0; i < kSize; ++i) {
    ASSERT_EQ(treap[i], elements[i]);
  }
}

TEST(TreapTest, SplitAtZero) {
  Aads::Treap<int> treap = {1, 2, 3, 4, 5};
  auto [left, right] = std::move(treap).Split(0);
  ASSERT_EQ(left.Size(), 0);
  ASSERT_EQ(right.Size(), 5);
}

TEST(TreapTest, SplitAtEnd) {
  Aads::Treap<int> treap = {1, 2, 3, 4, 5};
  auto [left, right] = std::move(treap).Split(treap.Size());
  ASSERT_EQ(left.Size(), 5);
  ASSERT_EQ(right.Size(), 0);
}

TEST(TreapTest, Split) {
  Aads::Treap<int> treap = {1, 2, 3, 4, 5};
  auto [left, right] = std::move(treap).Split(1);
  ASSERT_EQ(left.Size(), 1);
  ASSERT_EQ(right.Size(), 4);
}

TEST(TreapTest, SplitStress) {
  const int kSize = 1234;
  const int kLeftSize = 345;
  const int kRightSize = kSize - kLeftSize;

  Aads::Treap<int> treap;

  for (size_t i = 0; i < kSize; ++i) {
    treap.Insert(i, i);
  }
  auto [left, right] = std::move(treap).Split(kLeftSize);
  ASSERT_EQ(treap.Size(), 0);
  ASSERT_EQ(left.Size(), kLeftSize);
  ASSERT_EQ(right.Size(), kRightSize);

  for (size_t i = 0; i < kLeftSize; ++i) {
    ASSERT_EQ(left[i], i);
  }
  for (size_t i = 0; i < kRightSize; ++i) {
    ASSERT_EQ(right[i], i + kLeftSize);
  }
}

TEST(TreapTest, Merge) {
  Aads::Treap<int> left = {1, 2, 3, 4};
  Aads::Treap<int> right = {2, 3, 4, 5};
  auto merge = Aads::Treap<int>::Merge(std::move(left), std::move(right));
  EXPECT_EQ(merge.Size(), 8);

  left = {1, 2, 3, 4};
  right = {};
  merge = Aads::Treap<int>::Merge(std::move(left), std::move(right));
  EXPECT_EQ(merge.Size(), 4);

  left = {};
  right = {1, 2, 3, 4};
  merge = Aads::Treap<int>::Merge(std::move(left), std::move(right));
  EXPECT_EQ(merge.Size(), 4);
}

TEST(TreapTest, MergeStress) {
  const int kSize = 1234;
  const int kLeftSize = 345;
  const int kRightSize = kSize - kLeftSize;

  Aads::Treap<int> left;
  Aads::Treap<int> right;

  for (size_t i = 0; i < kLeftSize; ++i) {
    left.Insert(i, i);
  }
  for (size_t i = 0; i < kRightSize; ++i) {
    right.Insert(i, i);
  }

  auto merge = Aads::Treap<int>::Merge(std::move(left), std::move(right));
  EXPECT_EQ(merge.Size(), kSize);
  EXPECT_EQ(left.Size(), 0);
  EXPECT_EQ(right.Size(), 0);

  for (size_t i = 0; i < kLeftSize; ++i) {
    EXPECT_EQ(merge[i], i);
  }
  for (size_t i = 0; i < kRightSize; ++i) {
    EXPECT_EQ(merge[i + kLeftSize], i);
  }
}

TEST(TreapTest, InsertAndMin) {
  Aads::Treap<int> treap;

  treap.Insert(0, 10);
  treap.Insert(1, 5);
  treap.Insert(1, 20);

  EXPECT_EQ(treap[0], 10);
  EXPECT_EQ(treap[1], 20);
  EXPECT_EQ(treap[2], 5);

  EXPECT_EQ(treap.Min(0, 3), 5);
  EXPECT_EQ(treap.Min(0, 2), 10);
  EXPECT_EQ(treap.Min(1, 3), 5);
  EXPECT_EQ(treap.Min(0, 1), 10);
  EXPECT_EQ(treap.Min(1, 2), 20);
  EXPECT_EQ(treap.Min(2, 3), 5);
}

TEST(TreapTest, Reverse) {
  Aads::Treap<int> treap;

  treap.Insert(0, 1);
  treap.Insert(1, 2);
  treap.Insert(2, 3);
  treap.Insert(3, 4);

  treap.Reverse(1, 3);

  EXPECT_EQ(treap.Min(0, 2), 1);
  EXPECT_EQ(treap.Min(1, 4), 2);
}
