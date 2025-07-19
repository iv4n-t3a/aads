#include <gtest/gtest.h>

#include <functional>
#include <vector>

#include "segment_tree.hpp"

class SegmentTreeTest : public ::testing::Test {
 protected:
  using Func = std::function<int(int, int)>;
  Func min_func = [](int a, int b) { return std::min(a, b); };
  Func sum_func = [](int a, int b) { return a + b; };
};

TEST_F(SegmentTreeTest, ConstructAndQueryMin) {
  std::vector<int> data = {5, 2, 6, 3, 7, 1, 4};
  SegmentTree<int, Func> seg_tree(data.begin(), data.end(), min_func);

  EXPECT_EQ(seg_tree.Calc(0, 7), 1);
  EXPECT_EQ(seg_tree.Calc(1, 4), 2);
  EXPECT_EQ(seg_tree.Calc(3, 6), 1);
}

TEST_F(SegmentTreeTest, ConstructAndQuerySum) {
  std::vector<int> data = {5, 2, 6, 3, 7, 1, 4};
  SegmentTree<int, Func> seg_tree(data.begin(), data.end(), sum_func);

  EXPECT_EQ(seg_tree.Calc(0, 7), 28);
  EXPECT_EQ(seg_tree.Calc(1, 4), 11);
  EXPECT_EQ(seg_tree.Calc(3, 6), 11);
}

TEST_F(SegmentTreeTest, UpdateValue) {
  std::vector<int> data = {5, 2, 6, 3, 7, 1, 4};
  SegmentTree<int, Func> seg_tree(data.begin(), data.end(), min_func);

  seg_tree.Set(3, 0);
  EXPECT_EQ(seg_tree.Calc(0, 7), 0);
  EXPECT_EQ(seg_tree.Calc(3, 6), 0);
}

TEST_F(SegmentTreeTest, Size) {
  std::vector<int> data = {5, 2, 6, 3, 7, 1, 4};
  SegmentTree<int, Func> seg_tree(data.begin(), data.end(), min_func);
  EXPECT_EQ(seg_tree.Size(), 7);
}
