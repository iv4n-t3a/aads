#include <gtest/gtest.h>
#include "LCA/lca.hpp"

TEST(LCATest, SimpleTree) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);

  Aads::LCA<Aads::Graph<int>, int> lca(graph, 0);
  
  EXPECT_EQ(lca.GetLca(1, 2), 0);
  EXPECT_EQ(lca.Depth(0), 0);
  EXPECT_EQ(lca.Depth(1), 1);
  EXPECT_EQ(lca.Depth(2), 1);
}

TEST(LCATest, LinearTree) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);

  Aads::LCA<Aads::Graph<int>, int> lca(graph, 0);
  
  EXPECT_EQ(lca.GetLca(0, 3), 0);
  EXPECT_EQ(lca.GetLca(1, 3), 1);
  EXPECT_EQ(lca.GetLca(2, 3), 2);
}

TEST(LCATest, ComplexTree) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(1, 4);
  graph.AddEdge(2, 5);

  Aads::LCA<Aads::Graph<int>, int> lca(graph, 0);
  
  EXPECT_EQ(lca.GetLca(3, 4), 1);
  EXPECT_EQ(lca.GetLca(3, 5), 0);
  EXPECT_EQ(lca.GetLca(4, 5), 0);
}

TEST(LCATest, SameNode) {
  Aads::Graph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);

  Aads::LCA<Aads::Graph<int>, int> lca(graph, 0);
  
  EXPECT_EQ(lca.GetLca(1, 1), 1);
  EXPECT_EQ(lca.GetLca(2, 2), 2);
}
