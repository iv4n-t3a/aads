#include <gtest/gtest.h>
#include "MinmaxHeap/minmax_heap.hpp"

TEST(MinMaxHeapTest, InsertAndGetMin) {
  Aads::MinMaxHeap<int> heap;
  
  heap.Insert(5);
  heap.Insert(3);
  heap.Insert(7);
  
  EXPECT_EQ(heap.GetMin(), 3);
  EXPECT_EQ(heap.Size(), 3);
}

TEST(MinMaxHeapTest, InsertAndGetMax) {
  Aads::MinMaxHeap<int> heap;
  
  heap.Insert(5);
  heap.Insert(3);
  heap.Insert(7);
  
  EXPECT_EQ(heap.GetMax(), 7);
}

TEST(MinMaxHeapTest, ExtractMin) {
  Aads::MinMaxHeap<int> heap;
  
  heap.Insert(5);
  heap.Insert(3);
  heap.Insert(7);
  heap.Insert(1);
  
  EXPECT_EQ(heap.GetMin(), 1);
  heap.ExtractMin();
  EXPECT_EQ(heap.GetMin(), 3);
  EXPECT_EQ(heap.Size(), 3);
}

TEST(MinMaxHeapTest, ExtractMax) {
  Aads::MinMaxHeap<int> heap;
  
  heap.Insert(5);
  heap.Insert(3);
  heap.Insert(7);
  heap.Insert(9);
  
  EXPECT_EQ(heap.GetMax(), 9);
  heap.ExtractMax();
  EXPECT_EQ(heap.GetMax(), 7);
  EXPECT_EQ(heap.Size(), 3);
}

TEST(MinMaxHeapTest, Clear) {
  Aads::MinMaxHeap<int> heap;
  
  heap.Insert(5);
  heap.Insert(3);
  heap.Insert(7);
  
  heap.Clear();
  EXPECT_EQ(heap.Size(), 0);
}

TEST(MinMaxHeapTest, Emplace) {
  Aads::MinMaxHeap<int> heap;
  
  heap.Emplace(5);
  heap.Emplace(3);
  heap.Emplace(7);
  
  EXPECT_EQ(heap.GetMin(), 3);
  EXPECT_EQ(heap.GetMax(), 7);
}

TEST(MinMaxHeapTest, LargeHeap) {
  Aads::MinMaxHeap<int> heap;
  
  for (int i = 0; i < 100; ++i) {
    heap.Insert(i);
  }
  
  EXPECT_EQ(heap.GetMin(), 0);
  EXPECT_EQ(heap.GetMax(), 99);
  EXPECT_EQ(heap.Size(), 100);
}
