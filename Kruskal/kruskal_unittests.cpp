#include <gtest/gtest.h>
#include "Kruskal/kruskal.hpp"

TEST(KruskalTest, SimpleTree) {
  std::vector<Aads::Edge> edges = {
    {0, 1, 1},
    {1, 2, 2},
    {0, 2, 3}
  };

  int mst_weight = Aads::Kruskal(3, edges);
  
  EXPECT_EQ(mst_weight, 3);  // 1 + 2
}

TEST(KruskalTest, DisconnectedGraph) {
  std::vector<Aads::Edge> edges = {
    {0, 1, 1},
    {2, 3, 2}
  };

  int mst_weight = Aads::Kruskal(4, edges);
  
  EXPECT_EQ(mst_weight, 3);  // 1 + 2
}

TEST(KruskalTest, CompleteGraph) {
  std::vector<Aads::Edge> edges = {
    {0, 1, 4},
    {0, 2, 3},
    {1, 2, 1},
    {1, 3, 2},
    {2, 3, 5}
  };

  int mst_weight = Aads::Kruskal(4, edges);
  
  EXPECT_EQ(mst_weight, 6);  // 1 + 2 + 3
}

TEST(KruskalTest, SingleEdge) {
  std::vector<Aads::Edge> edges = {
    {0, 1, 10}
  };

  int mst_weight = Aads::Kruskal(2, edges);
  
  EXPECT_EQ(mst_weight, 10);
}

TEST(KruskalTest, NoEdges) {
  std::vector<Aads::Edge> edges;

  int mst_weight = Aads::Kruskal(3, edges);
  
  EXPECT_EQ(mst_weight, 0);
}
