#include <iostream>
#include <istream>
#include <span>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Color { WHITE, GREY, BLACK };

template <typename T, bool is_directed = false>
class Graph {
 public:
  using VertexT = T;
  using EdgeT = std::pair<VertexT, VertexT>;

  size_t CountVertexs() const { return adj_.size(); }
  size_t CountEdges() const { return edgecount_; }

  void AddEdge(VertexT vertex_from, VertexT vertex_to) {
    edgecount_ += 1;

    if (not adj_.contains(vertex_from)) {
      adj_[vertex_from] = {};
    }
    if (not adj_.contains(vertex_to)) {
      adj_[vertex_to] = {};
    }

    adj_[vertex_from].push_back(vertex_to);
    if (not is_directed) {
      adj_[vertex_to].push_back(vertex_from);
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
  if (visitor.IsVisited(vertex)) {
    return;
  }

  visitor.Explore(vertex);

  for (int adj_vertex : graph.GetAdj(vertex)) {
    DFS(graph, adj_vertex, visitor);
  }

  visitor.Leave(vertex);
}

template <typename Vertex>
class Visitor {
 public:
  void Explore(Vertex vertex) { visited_.insert(vertex); }
  void Leave(Vertex vertex) { std::ignore = vertex; }
  bool IsVisited(Vertex vertex) const { return visited_.contains(vertex); }
  std::unordered_set<Vertex> GetVisited() { return visited_; }

 private:
  std::unordered_set<Vertex> visited_;
};

std::vector<std::vector<int>> FindComps(const Graph<int>& graph) {
  std::vector<std::vector<int>> comps;
  std::vector<bool> visited(graph.CountVertexs());

  for (size_t i = 0; i < graph.CountVertexs(); ++i) {
    if (visited[i]) {
      continue;
    }

    Visitor<int> visitor;
    DFS(graph, i, visitor);
    comps.push_back(std::vector<int>(visitor.GetVisited().begin(),
                                     visitor.GetVisited().end()));

    for (int vertex : visitor.GetVisited()) {
      visited[vertex] = true;
    }
  }

  return comps;
}

Graph<int> InputGraph(std::istream& inp) {
  size_t vertexs;
  size_t edges;

  inp >> vertexs >> edges;

  Graph<int> graph;

  for (size_t i = 0; i < edges; ++i) {
    int vertex1;
    int vertex2;

    inp >> vertex1 >> vertex2;

    graph.AddEdge(vertex1 - 1, vertex2 - 1);
  }

  return graph;
}

void PrintComps(std::ostream& out, std::vector<std::vector<int>> comps) {
  out << comps.size() << "\n";

  for (std::vector<int> comp : comps) {
    out << comp.size() << "\n";
    for (int vertex : comp) {
      out << vertex + 1 << " ";
    }
    out << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Graph<int> graph = InputGraph(std::cin);
  auto comps = FindComps(graph);
  PrintComps(std::cout, comps);
}
