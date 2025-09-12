#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <random>
#include <stdexcept>
#include <vector>

#include "LRU/lru.hpp"

TEST(LRUTest, BasicUsage) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_TRUE(lru.Contains(3));
  ASSERT_TRUE(lru.Contains(4));
  ASSERT_TRUE(lru.Contains(5));
}

TEST(LRUTest, ItemsAccess) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  ASSERT_THROW(lru.GetWithoutUse(1), std::out_of_range);
  ASSERT_THROW(lru.GetWithoutUse(2), std::out_of_range);
  ASSERT_EQ(lru.GetWithoutUse(3), 3);
  ASSERT_EQ(lru.GetWithoutUse(4), 4);
  ASSERT_EQ(lru.GetWithoutUse(5), 5);
}

TEST(LRUTest, Use) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;
  lru.Use(4);
  lru[6] = 6;
  lru[7] = 7;

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_FALSE(lru.Contains(3));
  ASSERT_TRUE(lru.Contains(4));
  ASSERT_FALSE(lru.Contains(5));
  ASSERT_TRUE(lru.Contains(6));
  ASSERT_TRUE(lru.Contains(7));
}

TEST(LRUTest, UseLeastUsed) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;
  lru.Use(3);
  lru[6] = 6;

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_TRUE(lru.Contains(3));
  ASSERT_FALSE(lru.Contains(4));
  ASSERT_TRUE(lru.Contains(5));
  ASSERT_TRUE(lru.Contains(6));
}

TEST(LRUTest, RemoveLeastUsed) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  lru.RemoveLeastUsed();

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_FALSE(lru.Contains(3));
  ASSERT_TRUE(lru.Contains(4));
  ASSERT_TRUE(lru.Contains(5));
}

TEST(LRUTest, Remove) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  lru.Remove(4);

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_TRUE(lru.Contains(3));
  ASSERT_FALSE(lru.Contains(4));
  ASSERT_TRUE(lru.Contains(5));
}

TEST(LRUTest, RemoveLast) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  lru.Remove(5);

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_TRUE(lru.Contains(3));
  ASSERT_TRUE(lru.Contains(4));
  ASSERT_FALSE(lru.Contains(5));
}

TEST(LRUTest, UpdateLimit) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  lru.UpdateLimit(1);

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_FALSE(lru.Contains(3));
  ASSERT_FALSE(lru.Contains(4));
  ASSERT_TRUE(lru.Contains(5));
}

TEST(LRUTest, IncreaseLimit) {
  Aads::LruCache<int, int> lru(3);

  lru[1] = 1;
  lru[2] = 2;
  lru[3] = 3;
  lru[4] = 4;
  lru[5] = 5;

  lru.UpdateLimit(4);

  lru[6] = 6;

  ASSERT_FALSE(lru.Contains(1));
  ASSERT_FALSE(lru.Contains(2));
  ASSERT_TRUE(lru.Contains(3));
  ASSERT_TRUE(lru.Contains(4));
  ASSERT_TRUE(lru.Contains(5));
  ASSERT_TRUE(lru.Contains(6));
}

TEST(LRUTest, StressInsert) {
  const size_t kLimit = 10000;
  const size_t kInserts = 100000;

  Aads::LruCache<int, int> lru(kLimit);

  for (size_t i = 0; i < kInserts; ++i) {
    lru[i] = i;
  }

  for (size_t i = 0; i < kInserts - kLimit; ++i) {
    ASSERT_FALSE(lru.Contains(i));
  }
  for (size_t i = kInserts - kLimit; i < kInserts; ++i) {
    ASSERT_TRUE(lru.Contains(i));
    ASSERT_EQ(lru[i], i);
  }
}
