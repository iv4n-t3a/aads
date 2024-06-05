#include <cstdint>
#include <functional>
#include <iostream>
#include <span>
#include <vector>

template <typename T>
class SparseTable {
 public:
  SparseTable() = default;

  template <typename Iter>
  SparseTable(Iter begin, Iter end, std::function<T(T, T)> func) : func_(func) {
    size_ = std::distance(begin, end);
    table_.resize(Log2(size_) + 1);
    table_[0].resize(size_);
    std::copy(begin, end, table_[0].begin());

    for (size_t i = 1; i < table_.size(); i++) {
      table_[i].resize(size_ - Pow2(i));
      for (size_t j = 0; j < table_[i].size(); j++) {
        table_[i][j] = func_(table_[i - 1][j], table_[i - 1][j + Pow2(i - 1)]);
      }
    }
  }

  int Calc(size_t left, size_t right) const {
    size_t log = Log2(right - left + 1);
    return func_(table_[log][left], table_[log][right - Pow2(log) + 1]);
  }

 private:
  static uint64_t Pow2(int num) { return 1ULL << num; }

  static int Log2(uint64_t value) {
    int res = 0;
    while (value >= (1ULL << (res + 1))) {
      res += 1;
    }
    return res;
  }

  int size_;
  std::function<T(T, T)> func_;
  std::vector<std::vector<T>> table_;
};

template <typename T, bool is_directed = false>
class Graph {
 public:
  using VertexT = T;
  using EdgeT = std::pair<VertexT, VertexT>;

  size_t CountVertexs() const { return adj_.size(); }
  size_t CountEdges() const { return edgecount_; }

  void AddEdge(VertexT from, VertexT to) {
    edgecount_ += 1;

    if (not adj_.contains(from)) {
      adj_[from] = {};
    }
    if (not adj_.contains(to)) {
      adj_[to] = {};
    }

    adj_[from].push_back(to);
    if (not is_directed) {
      adj_[to].push_back(from);
    }
  }

  std::span<const VertexT> GetAdj(VertexT vertex) const {
    if (not adj_.contains(vertex)) {
      return std::span<const VertexT>();
    }
    return std::span(adj_.at(vertex));
  }

 private:
  size_t edgecount_ = 0;
  std::unordered_map<VertexT, std::vector<VertexT>> adj_;
};

template <typename Graph, typename Vertex, typename Visitor>
void DFS(const Graph& graph, const Vertex& vertex, Visitor& visitor) {
  visitor.Explore(vertex);

  for (int vertex2 : graph.GetAdj(vertex)) {
    if (visitor.IsVisited(vertex2)) {
      visitor.BackEdge(vertex, vertex2);
    } else {
      DFS(graph, vertex2, visitor);
      visitor.TreeEdge(vertex, vertex2);
    }
  }

  visitor.Leave(vertex);
}

template <typename Vertex>
class LCAVisitor {
 public:
  void Explore(Vertex vertex) {
    order_.push_back(vertex);
    first_[vertex] = time_;
    depths_[vertex] = depth_;
    depth_ += 1;
    time_ += 1;
  }
  void Leave(Vertex vertex) {
    std::ignore = vertex;
    depth_ -= 1;
    time_ += 1;
  }
  bool IsVisited(Vertex vertex) { return first_.contains(vertex); }

  void TreeEdge(Vertex vert1, Vertex vert2) {
    order_.push_back(vert1);
    std::ignore = vert2;
  }

  void BackEdge(Vertex vert, Vertex vert2) {
    std::ignore = vert;
    std::ignore = vert2;
  }

  const std::unordered_map<Vertex, int>& Depth() { return depths_; }
  const std::unordered_map<Vertex, int>& First() { return first_; }
  std::vector<Vertex>&& Order() { return std::move(order_); }

 private:
  int depth_ = 0;
  int time_ = 0;

  std::unordered_map<Vertex, int> depths_;
  std::unordered_map<Vertex, int> first_;
  std::vector<Vertex> order_;
};

template <typename Graph, typename Vertex>
class LCA {
 public:
  LCA(const Graph& graph, Vertex root) {
    LCAVisitor<Vertex> visitor;
    DFS(graph, root, visitor);
    depth_ = visitor.Depth();
    first_ = visitor.First();
    std::vector<int> order = visitor.Order();

    order_ = SparseTable<Vertex>(
        order.begin(), order.end(), [&](Vertex vert1, Vertex vert2) {
          return depth_[vert1] < depth_[vert2] ? vert1 : vert2;
        });
  }

  Vertex GetLca(Vertex vert1, Vertex vert2) const {
    if (first_.at(vert1) > first_.at(vert2)) {
      std::swap(vert1, vert2);
    }
    return order_.Calc(first_.at(vert1), first_.at(vert2));
  }

  int Depth(Vertex vert) const { return depth_.at(vert); }

 private:
  SparseTable<Vertex> order_;
  std::unordered_map<Vertex, int> depth_;
  std::unordered_map<Vertex, int> first_;
};

Graph<int> InputGraph(std::istream& inp) {
  int verts;
  inp >> verts;

  Graph<int> graph;

  for (int i = 0; i < verts - 1; ++i) {
    int vert1;
    int vert2;
    inp >> vert1 >> vert2;
    graph.AddEdge(vert1 - 1, vert2 - 1);
  }

  return graph;
}

template <typename LCA>
void ProcessQuery(std::istream& inp, std::ostream& outp, const LCA& lca) {
  int vert1;
  int vert2;
  inp >> vert1 >> vert2;

  int distance = lca.Depth(vert1 - 1) + lca.Depth(vert2 - 1) -
                 2 * lca.Depth(lca.GetLca(vert1 - 1, vert2 - 1));
  outp << distance << std::endl;
}

int main() {
  Graph<int> graph = InputGraph(std::cin);
  LCA lca(graph, 0);

  size_t queries;
  std::cin >> queries;
  for (size_t i = 0; i < queries; ++i) {
    ProcessQuery(std::cin, std::cout, lca);
  }
}
