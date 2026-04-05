#include <gtest/gtest.h>
#include "Khun/khun.hpp"

TEST(KhunTest, SimpleMatching) {
  Aads::GraphT graph;
  
  // Left vertices: 0, 1
  // Right vertices: 0, 1
  graph.AddVertexToLeft({0, false});
  graph.AddVertexToLeft({1, false});
  
  graph.AddEdge({{0, false}, {0, true}});
  graph.AddEdge({{1, false}, {1, true}});

  auto matching = Aads::FindMaxMatching<Aads::GraphT, Aads::Vertex, Aads::VertexHash>(graph);
  
  EXPECT_EQ(matching.size(), 2);
}

TEST(KhunTest, NoMatching) {
  Aads::GraphT graph;
  
  graph.AddVertexToLeft({0, false});
  // No edges added

  auto matching = Aads::FindMaxMatching<Aads::GraphT, Aads::Vertex, Aads::VertexHash>(graph);
  
  EXPECT_EQ(matching.size(), 0);
}

TEST(KhunTest, PartialMatching) {
  Aads::GraphT graph;
  
  graph.AddVertexToLeft({0, false});
  graph.AddVertexToLeft({1, false});
  graph.AddVertexToLeft({2, false});
  
  // Only 2 right vertices for 3 left vertices
  graph.AddEdge({{0, false}, {0, true}});
  graph.AddEdge({{1, false}, {1, true}});
  graph.AddEdge({{2, false}, {0, true}});

  auto matching = Aads::FindMaxMatching<Aads::GraphT, Aads::Vertex, Aads::VertexHash>(graph);
  
  EXPECT_LE(matching.size(), 2);  // At most 2 matches possible
}

TEST(KhunTest, CompleteMatching) {
  Aads::GraphT graph;
  
  // Complete bipartite graph K_{3,3}
  for (size_t i = 0; i < 3; ++i) {
    graph.AddVertexToLeft({i, false});
    for (size_t j = 0; j < 3; ++j) {
      graph.AddEdge({{i, false}, {j, true}});
    }
  }

  auto matching = Aads::FindMaxMatching<Aads::GraphT, Aads::Vertex, Aads::VertexHash>(graph);
  
  EXPECT_EQ(matching.size(), 3);  // Perfect matching
}
