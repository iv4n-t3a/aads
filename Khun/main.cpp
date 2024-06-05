#include <iostream>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T, typename E = std::pair<T, T>, bool is_directed = false>
class AbstractGraph {
 public:
  using VertexT = T;
  using EdgeT = E;

  virtual size_t CountVertices() const = 0;
  virtual size_t CountEdges() const = 0;
  virtual void AddEdge(EdgeT edge) = 0;
  virtual std::span<const EdgeT> GetAdj(VertexT vertex) const = 0;
  virtual ~AbstractGraph() = default;
};

template <typename T, typename E = std::pair<T, T>, bool is_directed = false>
class AbstractBipartGraph {
 public:
  using VertexT = T;
  using EdgeT = E;

  virtual std::span<const VertexT> LeftPart() const = 0;
  virtual void AddVertexToLeft(VertexT vertex) = 0;
  virtual ~AbstractBipartGraph() = default;
};

template <typename T, typename E = std::pair<T, T>, bool is_directed = false,
          typename Hash = std::hash<T>>
class GraphImpl : public AbstractGraph<T, E, is_directed> {
 public:
  using VertexT = T;
  using EdgeT = E;

  size_t CountVertices() const override { return adj_.size(); }
  size_t CountEdges() const override { return edgecount_; }

  void AddEdge(EdgeT edge) override {
    edgecount_ += 1;

    if (not adj_.contains(edge.first)) {
      adj_[edge.first] = {};
    }
    if (not adj_.contains(edge.second)) {
      adj_[edge.second] = {};
    }

    adj_[edge.first].push_back(edge);
    if constexpr (not is_directed) {
      adj_[edge.second].push_back(edge);
    }
  }

  std::span<const EdgeT> GetAdj(VertexT vertex) const override {
    if (not adj_.contains(vertex)) {
      return std::span<const EdgeT>();
    }
    return std::span(adj_.at(vertex));
  }

 private:
  size_t edgecount_ = 0;
  std::unordered_map<VertexT, std::vector<EdgeT>, Hash> adj_;
};

template <typename T, typename E = std::pair<T, T>, bool is_directed = false,
          typename Hash = std::hash<T>>
class BipartGraphImpl : public GraphImpl<T, E, is_directed, Hash>,
                        public AbstractBipartGraph<T, E> {
 public:
  using VertexT = T;
  using EdgeT = E;

  std::span<const VertexT> LeftPart() const override {
    return std::span(left_);
  }

  void AddVertexToLeft(VertexT vertex) override { left_.push_back(vertex); }

 private:
  std::vector<VertexT> left_;
};

template <typename Graph, typename Vertex, typename VertexHash>
bool FindIncreasingChainHelper(
    const Graph& graph,
    const std::unordered_map<Vertex, Vertex, VertexHash>& matching,
    Vertex start, std::vector<Vertex>& found,
    std::unordered_set<Vertex, VertexHash>& visited) {
  if (visited.contains(start)) {
    return false;
  }
  visited.insert(start);
  for (auto edge : graph.GetAdj(start)) {
    if (not matching.contains(edge.second)) {
      found.push_back(edge.second);
      return true;
    }
    found.push_back(edge.second);
    found.push_back(matching.at(edge.second));
    bool res = FindIncreasingChainHelper(
        graph, matching, matching.at(edge.second), found, visited);
    if (res) {
      return true;
    }
    found.pop_back();
    found.pop_back();
  }
  return false;
}

template <typename Graph, typename Vertex, typename VertexHash>
std::vector<Vertex> FindIncreasingChain(
    const Graph& graph,
    const std::unordered_map<Vertex, Vertex, VertexHash>& matching,
    Vertex start) {
  std::vector<Vertex> res;
  std::unordered_set<Vertex, VertexHash> visited;
  res.push_back(start);
  bool is_succes = FindIncreasingChainHelper<Graph, Vertex, VertexHash>(
      graph, matching, start, res, visited);
  if (not is_succes) {
    return {};
  }
  return res;
}

template <typename Vertex, typename VertexHash>
void AlternateMatching(std::unordered_map<Vertex, Vertex, VertexHash>& matching,
                       const std::vector<Vertex>& incchain) {
  for (size_t i = 0; i < incchain.size(); i += 2) {
    Vertex left_vert = incchain[i];
    Vertex right_vert = incchain[i + 1];
    matching[right_vert] = left_vert;
  }
}

template <typename BipartitionGraph, typename Vertex, typename VertexHash>
std::unordered_map<Vertex, Vertex, VertexHash> FindMaxMatching(
    const BipartitionGraph& graph) {
  std::unordered_map<Vertex, Vertex, VertexHash> matching;

  for (const auto& vert : graph.LeftPart()) {
    std::vector<Vertex> incchain = FindIncreasingChain(graph, matching, vert);
    AlternateMatching(matching, incchain);
  }

  return matching;
}

struct Vertex {
  size_t index;
  bool is_right = false;

  bool operator==(const Vertex& other) const {
    return index == other.index and is_right == other.is_right;
  }
};

struct VertexHash {
 public:
  std::size_t operator()(const Vertex& vert) const {
    return vert.index + (vert.is_right ? kBigNumber : 0);
  }

 private:
  const size_t kBigNumber = 1474747489162319795;
};

using GraphT =
    BipartGraphImpl<Vertex, std::pair<Vertex, Vertex>, false, VertexHash>;

GraphT InputGraph(std::istream& inp) {
  size_t left_size;
  size_t right_size;

  inp >> left_size >> right_size;

  GraphT res;

  for (size_t left_vert = 0; left_vert < left_size; ++left_vert) {
    size_t right_vert;
    inp >> right_vert;

    res.AddVertexToLeft({left_vert, false});
    while (right_vert != 0) {
      res.AddEdge({{left_vert, false}, {right_vert - 1, true}});
      inp >> right_vert;
    }
  }

  return res;
}

void PrintMatching(
    std::ostream& outp,
    const std::unordered_map<Vertex, Vertex, VertexHash>& matching) {
  outp << matching.size() << "\n";
  for (auto pair : matching) {
    outp << pair.second.index + 1 << " " << pair.first.index + 1 << "\n";
  }
}

int main() {
  GraphT graph = InputGraph(std::cin);
  std::unordered_map<Vertex, Vertex, VertexHash> matching =
      FindMaxMatching<GraphT, Vertex, VertexHash>(graph);
  PrintMatching(std::cout, matching);
}
