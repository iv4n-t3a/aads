#include <gtest/gtest.h>
#include "DFS/dfs.hpp"

TEST(DFSTest, SingleComponent) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 0);

  auto comps = Aads::FindComps(graph);
  
  EXPECT_EQ(comps.size(), 1);
  EXPECT_EQ(comps[0].size(), 3);
}

TEST(DFSTest, MultipleComponents) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(2, 3);

  auto comps = Aads::FindComps(graph);
  
  EXPECT_EQ(comps.size(), 2);
}

TEST(DFSTest, VisitorPattern) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);

  Aads::Visitor<int> visitor;
  Aads::DFS(graph, 0, visitor);
  
  EXPECT_TRUE(visitor.IsVisited(0));
  EXPECT_TRUE(visitor.IsVisited(1));
  EXPECT_TRUE(visitor.IsVisited(2));
}

TEST(DFSTest, DisconnectedNodes) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(2, 3);
  graph.AddEdge(4, 5);

  auto comps = Aads::FindComps(graph);
  
  EXPECT_EQ(comps.size(), 3);
}
