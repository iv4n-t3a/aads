#include <gtest/gtest.h>
#include "Dijkstra/dijkstra.hpp"

TEST(DijkstraTest, SimpleGraph) {
  Aads::Graph<int> graph;
  graph.SetVerticesCount(3);
  graph.AddEdge(Aads::Edge<int>(0, 1, 1));
  graph.AddEdge(Aads::Edge<int>(1, 2, 2));

  Aads::Visitor<int> vis;
  Aads::Dijkstra(graph, 0, vis);
  
  EXPECT_EQ(vis.GetDistance(0), 0);
  EXPECT_EQ(vis.GetDistance(1), 1);
  EXPECT_EQ(vis.GetDistance(2), 3);
}

TEST(DijkstraTest, ShortestPath) {
  Aads::Graph<int> graph;
  graph.SetVerticesCount(4);
  graph.AddEdge(Aads::Edge<int>(0, 1, 10));
  graph.AddEdge(Aads::Edge<int>(0, 2, 5));
  graph.AddEdge(Aads::Edge<int>(2, 1, 3));
  graph.AddEdge(Aads::Edge<int>(1, 3, 1));

  Aads::Visitor<int> vis;
  Aads::Dijkstra(graph, 0, vis);
  
  EXPECT_EQ(vis.GetDistance(0), 0);
  EXPECT_EQ(vis.GetDistance(1), 8);  // 0->2->1
  EXPECT_EQ(vis.GetDistance(2), 5);
  EXPECT_EQ(vis.GetDistance(3), 9);  // 0->2->1->3
}

TEST(DijkstraTest, UnreachableNode) {
  Aads::Graph<int> graph;
  graph.SetVerticesCount(3);
  graph.AddEdge(Aads::Edge<int>(0, 1, 1));

  Aads::Visitor<int> vis;
  Aads::Dijkstra(graph, 0, vis);
  
  EXPECT_EQ(vis.GetDistance(0), 0);
  EXPECT_EQ(vis.GetDistance(1), 1);
  EXPECT_EQ(vis.GetDistance(2), 2009000999);  // kInfinity
}

TEST(DijkstraTest, SingleNode) {
  Aads::Graph<int> graph;
  graph.SetVerticesCount(1);

  Aads::Visitor<int> vis;
  Aads::Dijkstra(graph, 0, vis);
  
  EXPECT_EQ(vis.GetDistance(0), 0);
}
