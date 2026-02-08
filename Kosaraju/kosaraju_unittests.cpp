#include <gtest/gtest.h>
#include "Kosaraju/kosaraju.hpp"

TEST(KosarajuTest, SingleSCC) {
  Aads::DirGraph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 0);

  auto condensated = Aads::Condensate(graph);
  
  EXPECT_EQ(condensated[0], condensated[1]);
  EXPECT_EQ(condensated[1], condensated[2]);
}

TEST(KosarajuTest, MultipleSCCs) {
  Aads::DirGraph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 0);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 2);

  auto condensated = Aads::Condensate(graph);
  
  EXPECT_EQ(condensated[0], condensated[1]);
  EXPECT_EQ(condensated[2], condensated[3]);
  EXPECT_NE(condensated[0], condensated[2]);
}

TEST(KosarajuTest, LinearGraph) {
  Aads::DirGraph<int> graph;
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);

  auto condensated = Aads::Condensate(graph);
  
  // Each vertex is its own SCC
  EXPECT_NE(condensated[0], condensated[1]);
  EXPECT_NE(condensated[1], condensated[2]);
  EXPECT_NE(condensated[2], condensated[3]);
}

TEST(KosarajuTest, ComplexGraph) {
  Aads::DirGraph<int> graph;
  // Create two SCCs connected by a bridge
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 0);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 2);

  auto condensated = Aads::Condensate(graph);
  
  EXPECT_EQ(condensated[0], condensated[1]);
  EXPECT_EQ(condensated[2], condensated[3]);
  EXPECT_NE(condensated[0], condensated[2]);
}
