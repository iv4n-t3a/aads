#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "PersistantArray/persistant_array.hpp"

TEST(PersistentArrayTest, ConstructorEmpty) {
  std::vector<int> empty;
  Aads::PersistentArray<int> arr(empty.begin(), empty.end());
  EXPECT_EQ(arr.Size(), 0);
  EXPECT_EQ(arr.Versions(), 1);
}

TEST(PersistentArrayTest, ConstructorSingleElement) {
  std::vector<int> data = {42};
  Aads::PersistentArray<int> arr(data.begin(), data.end());
  EXPECT_EQ(arr.Size(), 1);
  EXPECT_EQ(arr.Versions(), 1);
  EXPECT_EQ(arr.Get(0), 42);
}

TEST(PersistentArrayTest, ConstructorMultipleElements) {
  std::vector<int> data = {1, 2, 3, 4};
  Aads::PersistentArray<int> arr(data.begin(), data.end());
  EXPECT_EQ(arr.Size(), 4);
  EXPECT_EQ(arr.Versions(), 1);
  EXPECT_EQ(arr.Get(0), 1);
  EXPECT_EQ(arr.Get(3), 4);
}

TEST(PersistentArrayTest, GetMultipleVersions) {
  std::vector<int> data = {1, 2, 3, 4};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  arr.Set(0, 1, 10);

  EXPECT_EQ(arr.Get(0, 0), 1);
  EXPECT_EQ(arr.Get(0, 1), 2);
  EXPECT_EQ(arr.Get(0, 2), 3);
  EXPECT_EQ(arr.Get(0, 3), 4);

  EXPECT_EQ(arr.Get(1, 0), 1);
  EXPECT_EQ(arr.Get(1, 1), 10);
  EXPECT_EQ(arr.Get(1, 2), 3);
  EXPECT_EQ(arr.Get(1, 3), 4);

  EXPECT_EQ(arr.Versions(), 2);
}

TEST(PersistentArrayTest, GetSingleElementArray) {
  std::vector<int> data = {42};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  arr.Set(0, 0, 100);
  EXPECT_EQ(arr.Get(0, 0), 42);
  EXPECT_EQ(arr.Get(1, 0), 100);
  EXPECT_EQ(arr.Versions(), 2);
}

TEST(PersistentArrayTest, SetMultipleTimes) {
  std::vector<int> data = {1, 2, 3};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  arr.Set(0, 0, 10);
  arr.Set(1, 1, 20);
  arr.Set(2, 2, 30);

  EXPECT_EQ(arr.Versions(), 4);

  EXPECT_EQ(arr.Get(0, 0), 1);
  EXPECT_EQ(arr.Get(0, 1), 2);
  EXPECT_EQ(arr.Get(0, 2), 3);

  EXPECT_EQ(arr.Get(1, 0), 10);
  EXPECT_EQ(arr.Get(1, 1), 2);
  EXPECT_EQ(arr.Get(1, 2), 3);

  EXPECT_EQ(arr.Get(2, 0), 10);
  EXPECT_EQ(arr.Get(2, 1), 20);
  EXPECT_EQ(arr.Get(2, 2), 3);

  EXPECT_EQ(arr.Get(3, 0), 10);
  EXPECT_EQ(arr.Get(3, 1), 20);
  EXPECT_EQ(arr.Get(3, 2), 30);
}

TEST(PersistentArrayTest, NonIntegerType) {
  std::vector<std::string> data = {"a", "b", "c"};
  Aads::PersistentArray<std::string> arr(data.begin(), data.end());

  EXPECT_EQ(arr.Size(), 3);
  EXPECT_EQ(arr.Get(0, 0), "a");
  EXPECT_EQ(arr.Get(0, 1), "b");
  EXPECT_EQ(arr.Get(0, 2), "c");

  arr.Set(0, 1, std::string("new"));
  EXPECT_EQ(arr.Get(1, 1), "new");
  EXPECT_EQ(arr.Get(1, 0), "a");
  EXPECT_EQ(arr.Get(1, 2), "c");
}

TEST(PersistentArrayTest, CornerCaseLargeIndex) {
  std::vector<int> data = {1, 2, 3, 4, 5};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  EXPECT_EQ(arr.Get(0, 0), 1);
  EXPECT_EQ(arr.Get(0, 4), 5);

  arr.Set(0, 4, 50);
  EXPECT_EQ(arr.Get(1, 4), 50);
  EXPECT_EQ(arr.Get(1, 0), 1);
}

TEST(PersistentArrayTest, CornerCaseZeroIndex) {
  std::vector<int> data = {1, 2, 3};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  arr.Set(0, 0, 100);
  EXPECT_EQ(arr.Get(1, 0), 100);
  EXPECT_EQ(arr.Get(1, 1), 2);
  EXPECT_EQ(arr.Get(1, 2), 3);
}

TEST(PersistentArrayTest, VersionsAndSize) {
  std::vector<int> data = {1, 2};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  EXPECT_EQ(arr.Size(), 2);
  EXPECT_EQ(arr.Versions(), 1);

  arr.Set(0, 0, 10);
  arr.Set(1, 1, 20);

  EXPECT_EQ(arr.Size(), 2);
  EXPECT_EQ(arr.Versions(), 3);
}

TEST(PersistentArrayTest, DefaultGetLatestVersion) {
  std::vector<int> data = {1, 2, 3};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  arr.Set(0, 1, 20);
  arr.Set(1, 2, 30);

  EXPECT_EQ(arr.Get(2), 30);
  EXPECT_EQ(arr.Get(1), 20);
  EXPECT_EQ(arr.Get(0), 1);
}
