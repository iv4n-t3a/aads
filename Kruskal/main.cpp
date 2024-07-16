#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

class DSU {
 public:
  DSU(size_t size) : ancestors_(size), rank_(size) {
    for (size_t i = 0; i < size; ++i) {
      ancestors_[i] = i;
    }
  }

  void Unite(size_t lhs, size_t rhs) {
    int lhs_anc = Find(lhs);
    int rhs_anc = Find(rhs);

    if (lhs_anc == rhs_anc) {
      return;
    }
    if (rank_[lhs_anc] < rank_[rhs_anc]) {
      std::swap(lhs_anc, rhs_anc);
    }
    rank_[lhs_anc] = std::max(rank_[lhs_anc], rank_[rhs_anc] + 1);
    ancestors_[rhs_anc] = lhs_anc;
  }

  bool AreSame(size_t lhs, size_t rhs) { return Find(lhs) == Find(rhs); }

 private:
  size_t Find(size_t idx) {
    if (ancestors_[idx] != idx) {
      ancestors_[idx] = Find(ancestors_[idx]);
    }
    return ancestors_[idx];
  }

  std::vector<size_t> ancestors_;
  std::vector<size_t> rank_;
};

struct Edge {
  int from;
  int to;
  int weight;

  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }
};

int main() {
  int vertex_count;
  int edges_count;

  std::cin >> vertex_count >> edges_count;

  std::vector<Edge> edges;

  for (size_t i = 0; i < edges_count; ++i) {
    int vert1;
    int vert2;
    int weight;

    std::cin >> vert1 >> vert2 >> weight;
    edges.push_back({vert1 - 1, vert2 - 1, weight});
  }

  std::sort(edges.begin(), edges.end());

  DSU dsu(vertex_count);
  int weight = 0;

  for (Edge edge : edges) {
    if (dsu.AreSame(edge.from, edge.to)) {
      continue;
    }
    dsu.Unite(edge.from, edge.to);
    weight += edge.weight;
  }

  std::cout << weight;
}
