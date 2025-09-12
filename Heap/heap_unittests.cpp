#include <gtest/gtest.h>

#include "Heap/heap.hpp"

namespace Aads {

class HeapTest : public ::testing::Test {
 protected:
  Heap<int> heap;
};

TEST_F(HeapTest, EmptyHeap) {
  EXPECT_EQ(0u, heap.Size());
}

TEST_F(HeapTest, Reserve) {
  heap.Reserve(100);
  EXPECT_EQ(0u, heap.Size());  // Size should still be 0
  // No direct way to test capacity, but we can insert elements
  for (int i = 0; i < 50; ++i) {
    heap.Insert(i);
  }
  EXPECT_EQ(50u, heap.Size());
}

TEST_F(HeapTest, InsertSingleElement) {
  heap.Insert(42);
  EXPECT_EQ(1u, heap.Size());
  EXPECT_EQ(42, heap.GetMax());
}

TEST_F(HeapTest, InsertMultipleElements) {
  heap.Insert(10);
  heap.Insert(30);
  heap.Insert(20);
  heap.Insert(40);

  EXPECT_EQ(4u, heap.Size());
  EXPECT_EQ(40, heap.GetMax());

  // Verify heap property
  heap.Insert(50);
  EXPECT_EQ(50, heap.GetMax());
  EXPECT_EQ(5u, heap.Size());
}

TEST_F(HeapTest, InsertRvalue) {
  heap.Insert(std::move(42));
  EXPECT_EQ(1u, heap.Size());
  EXPECT_EQ(42, heap.GetMax());
}

TEST_F(HeapTest, Emplace) {
  heap.Emplace(42);
  EXPECT_EQ(1u, heap.Size());
  EXPECT_EQ(42, heap.GetMax());

  heap.Emplace(50);
  EXPECT_EQ(2u, heap.Size());
  EXPECT_EQ(50, heap.GetMax());
}

TEST_F(HeapTest, ExtractMaxSingleElement) {
  heap.Insert(42);
  heap.ExtractMax();
  EXPECT_EQ(0u, heap.Size());
}

TEST_F(HeapTest, ExtractMaxMultipleElements) {
  heap.Insert(10);
  heap.Insert(30);
  heap.Insert(20);
  heap.Insert(40);

  heap.ExtractMax();  // Should remove 40
  EXPECT_EQ(3u, heap.Size());
  EXPECT_EQ(30, heap.GetMax());

  heap.ExtractMax();  // Should remove 30
  EXPECT_EQ(2u, heap.Size());
  EXPECT_EQ(20, heap.GetMax());
}

TEST_F(HeapTest, GetMaxConst) {
  heap.Insert(42);
  const Heap<int>& const_heap = heap;
  EXPECT_EQ(42, const_heap.GetMax());
}

TEST_F(HeapTest, LargeNumberOfElements) {
  const int N = 1000;
  for (int i = 0; i < N; ++i) {
    heap.Insert(i);
  }
  EXPECT_EQ(static_cast<size_t>(N), heap.Size());
  EXPECT_EQ(N - 1, heap.GetMax());

  // Verify max-heap property by extracting all elements
  int last = heap.GetMax();
  for (int i = 0; i < N; ++i) {
    int current = heap.GetMax();
    heap.ExtractMax();
    EXPECT_LE(current, last);
    last = current;
  }
}

TEST_F(HeapTest, DuplicateElements) {
  heap.Insert(42);
  heap.Insert(42);
  heap.Insert(42);

  EXPECT_EQ(3u, heap.Size());
  EXPECT_EQ(42, heap.GetMax());

  heap.ExtractMax();
  EXPECT_EQ(2u, heap.Size());
  EXPECT_EQ(42, heap.GetMax());
}

TEST_F(HeapTest, NegativeNumbers) {
  heap.Insert(-10);
  heap.Insert(-5);
  heap.Insert(-15);
  heap.Insert(0);

  EXPECT_EQ(4u, heap.Size());
  EXPECT_EQ(0, heap.GetMax());

  heap.ExtractMax();
  EXPECT_EQ(-5, heap.GetMax());
}

TEST_F(HeapTest, StringHeap) {
  Heap<std::string> string_heap;
  string_heap.Insert("banana");
  string_heap.Insert("apple");
  string_heap.Insert("cherry");

  EXPECT_EQ(3u, string_heap.Size());
  EXPECT_EQ("cherry", string_heap.GetMax());

  string_heap.ExtractMax();
  EXPECT_EQ("banana", string_heap.GetMax());
}

}  // namespace Aads
