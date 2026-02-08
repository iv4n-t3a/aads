#include <gtest/gtest.h>
#include "CutPoints/cut_points.hpp"

TEST(CutPointsTest, SimpleCutPoint) {
  std::vector<std::vector<int>> adj(3);
  adj[0].push_back(1);
  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[2].push_back(1);

  auto cut_points = Aads::CutPoints(adj);
  
  EXPECT_EQ(cut_points.size(), 1);
  EXPECT_TRUE(cut_points.contains(1));  // Node 1 is the cut point
}

TEST(CutPointsTest, NoCutPoints) {
  std::vector<std::vector<int>> adj(3);
  adj[0].push_back(1);
  adj[0].push_back(2);
  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[2].push_back(0);
  adj[2].push_back(1);

  auto cut_points = Aads::CutPoints(adj);
  
  EXPECT_EQ(cut_points.size(), 0);  // Triangle has no cut points
}

TEST(CutPointsTest, SingleEdge) {
  std::vector<std::vector<int>> adj(2);
  adj[0].push_back(1);
  adj[1].push_back(0);

  auto cut_points = Aads::CutPoints(adj);
  
  EXPECT_EQ(cut_points.size(), 0);  // No cut points in a single edge
}

TEST(CutPointsTest, StarGraph) {
  std::vector<std::vector<int>> adj(5);
  // Center node 0 connected to all others
  for (int i = 1; i < 5; ++i) {
    adj[0].push_back(i);
    adj[i].push_back(0);
  }

  auto cut_points = Aads::CutPoints(adj);
  
  EXPECT_EQ(cut_points.size(), 1);
  EXPECT_TRUE(cut_points.contains(0));  // Center is the cut point
}

TEST(CutPointsTest, ComplexGraph) {
  std::vector<std::vector<int>> adj(6);
  // Create a graph with multiple cut points
  adj[0].push_back(1);
  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[1].push_back(3);
  adj[2].push_back(1);
  adj[3].push_back(1);
  adj[3].push_back(4);
  adj[3].push_back(5);
  adj[4].push_back(3);
  adj[5].push_back(3);

  auto cut_points = Aads::CutPoints(adj);
  
  EXPECT_GE(cut_points.size(), 1);  // At least nodes 1 and 3 are cut points
}
