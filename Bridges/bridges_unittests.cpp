#include <gtest/gtest.h>
#include "Bridges/bridges.hpp"

TEST(BridgesTest, SimpleBridge) {
  std::vector<std::vector<int>> adj(3);
  adj[0].push_back(1);
  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[2].push_back(1);

  auto bridges = Aads::Bridges(adj);
  
  EXPECT_EQ(bridges.size(), 2);  // Two bridges: 0-1 and 1-2
}

TEST(BridgesTest, NoBridges) {
  std::vector<std::vector<int>> adj(3);
  adj[0].push_back(1);
  adj[0].push_back(2);
  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[2].push_back(0);
  adj[2].push_back(1);

  auto bridges = Aads::Bridges(adj);
  
  EXPECT_EQ(bridges.size(), 0);  // Triangle has no bridges
}

TEST(BridgesTest, SingleEdge) {
  std::vector<std::vector<int>> adj(2);
  adj[0].push_back(1);
  adj[1].push_back(0);

  auto bridges = Aads::Bridges(adj);
  
  EXPECT_EQ(bridges.size(), 1);
}

TEST(BridgesTest, DisconnectedGraph) {
  std::vector<std::vector<int>> adj(4);
  adj[0].push_back(1);
  adj[1].push_back(0);
  adj[2].push_back(3);
  adj[3].push_back(2);

  auto bridges = Aads::Bridges(adj);
  
  EXPECT_EQ(bridges.size(), 2);  // Two separate bridges
}

TEST(BridgesTest, ComplexGraph) {
  std::vector<std::vector<int>> adj(5);
  // Create a graph with one bridge
  adj[0].push_back(1);
  adj[0].push_back(2);
  adj[1].push_back(0);
  adj[1].push_back(2);
  adj[2].push_back(0);
  adj[2].push_back(1);
  adj[2].push_back(3);
  adj[3].push_back(2);
  adj[3].push_back(4);
  adj[4].push_back(3);

  auto bridges = Aads::Bridges(adj);
  
  EXPECT_EQ(bridges.size(), 2);  // Bridges: 2-3 and 3-4
}
