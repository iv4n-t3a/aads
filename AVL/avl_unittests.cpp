#include <gtest/gtest.h>
#include "AVL/avl.hpp"

TEST(AVLTreeTest, InsertAndContains) {
  Aads::Tree<int> tree;
  
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  
  EXPECT_TRUE(tree.Contains(5));
  EXPECT_TRUE(tree.Contains(3));
  EXPECT_TRUE(tree.Contains(7));
  EXPECT_FALSE(tree.Contains(1));
  EXPECT_FALSE(tree.Contains(10));
}

TEST(AVLTreeTest, Next) {
  Aads::Tree<int> tree;
  
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(1);
  tree.Insert(9);
  
  EXPECT_TRUE(tree.ContainsNext(0));
  EXPECT_EQ(tree.Next(0), 1);
  
  EXPECT_TRUE(tree.ContainsNext(1));
  EXPECT_EQ(tree.Next(1), 1);
  
  EXPECT_TRUE(tree.ContainsNext(2));
  EXPECT_EQ(tree.Next(2), 3);
  
  EXPECT_TRUE(tree.ContainsNext(5));
  EXPECT_EQ(tree.Next(5), 5);
  
  EXPECT_TRUE(tree.ContainsNext(6));
  EXPECT_EQ(tree.Next(6), 7);
  
  EXPECT_TRUE(tree.ContainsNext(9));
  EXPECT_EQ(tree.Next(9), 9);
  
  EXPECT_FALSE(tree.ContainsNext(10));
}

TEST(AVLTreeTest, DuplicateInsert) {
  Aads::Tree<int> tree;
  
  tree.Insert(5);
  tree.Insert(5);
  tree.Insert(5);
  
  EXPECT_TRUE(tree.Contains(5));
}

TEST(AVLTreeTest, LargeTree) {
  Aads::Tree<int> tree;
  
  // Insert many elements to test balancing
  for (int i = 0; i < 100; ++i) {
    tree.Insert(i);
  }
  
  // Check all elements are present
  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(tree.Contains(i));
  }
  
  // Check Next works correctly
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(tree.Next(i), i);
  }
}

TEST(AVLTreeTest, ReverseInsert) {
  Aads::Tree<int> tree;
  
  // Insert in reverse order to test right-heavy balancing
  for (int i = 10; i >= 0; --i) {
    tree.Insert(i);
  }
  
  for (int i = 0; i <= 10; ++i) {
    EXPECT_TRUE(tree.Contains(i));
  }
}

TEST(AVLTreeTest, EmptyTree) {
  Aads::Tree<int> tree;
  
  EXPECT_FALSE(tree.Contains(5));
  EXPECT_FALSE(tree.ContainsNext(5));
}
