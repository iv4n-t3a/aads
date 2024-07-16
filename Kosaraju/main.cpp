#include <algorithm>
#include <iostream>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Color { WHITE, GREY, BLACK };

template <typename T, bool IsDirected = false>
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
    if (not IsDirected) {
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

template <typename T>
class DirGraph : public Graph<T, true> {};

template <typename T>
DirGraph<T> Transponed(const DirGraph<T>& graph) {
  DirGraph<T> transponed;

  for (size_t vertex1 = 0; vertex1 < graph.CountVertexs(); ++vertex1) {
    for (size_t vertex2 : graph.GetAdj(vertex1)) {
      transponed.AddEdge(vertex2, vertex1);
    }
  }

  return transponed;
}

template <typename Graph, typename Vertex, typename Visitor>
void DFS(const Graph& graph, const Vertex& vertex, Visitor& visitor) {
  if (visitor.IsVisited(vertex)) {
    return;
  }

  visitor.Explore(vertex);

  for (int vertex2 : graph.GetAdj(vertex)) {
    DFS(graph, vertex2, visitor);
  }

  visitor.Leave(vertex);
}

template <typename Vertex>
class TOutVisitor {
 public:
  void Explore(Vertex vertex) { t_out_[vertex] = -1; }
  void Leave(Vertex vertex) { t_out_[vertex] = ++timer_; }
  bool IsVisited(Vertex vertex) { return t_out_[vertex] != 0; }
  std::unordered_map<Vertex, int> GetTOut() { return t_out_; }

 private:
  int timer_ = 0;
  std::unordered_map<Vertex, int> t_out_;
};

template <typename Vertex>
class Visitor {
 public:
  void Explore(Vertex vertex) { visited_.insert(vertex); }
  void Leave(Vertex vertex) {}
  bool IsVisited(Vertex vertex) { return visited_.contains(vertex); }
  std::unordered_set<Vertex> GetVisited() { return visited_; }

 private:
  std::unordered_set<Vertex> visited_;
};

std::unordered_map<int, int> BuildTOut(const DirGraph<int>& graph) {
  std::vector<int> t_out(graph.CountVertexs());
  TOutVisitor<int> t_out_visitor;

  for (size_t i = 0; i < graph.CountVertexs(); ++i) {
    if (t_out_visitor.IsVisited(i)) {
      continue;
    }
    DFS(graph, i, t_out_visitor);
  }

  return t_out_visitor.GetTOut();
}

std::vector<int> SortByTOut(const DirGraph<int>& graph) {
  std::unordered_map<int, int> t_out = BuildTOut(graph);
  std::vector<int> sorted(graph.CountVertexs());

  for (size_t i = 0; i < graph.CountVertexs(); ++i) {
    sorted[t_out[i] - 1] = i;
  }

  std::reverse(sorted.begin(), sorted.end());

  return sorted;
}

std::vector<int> Condensate(const DirGraph<int>& graph) {
  std::vector<int> sorted_by_t_out = SortByTOut(graph);
  DirGraph<int> transponed = Transponed(graph);

  std::vector<int> condensated(graph.CountVertexs());
  std::vector<bool> visited(graph.CountVertexs());
  int comp_count = 1;

  for (size_t vertex : sorted_by_t_out) {
    if (visited[vertex]) {
      continue;
    }

    Visitor<int> visitor;
    DFS(transponed, vertex, visitor);

    for (int comp_vertex : visitor.GetVisited()) {
      visited[comp_vertex] = true;
      if (condensated[comp_vertex] == 0) {
        condensated[comp_vertex] = comp_count;
      }
    }

    comp_count += 1;
  }

  return condensated;
}

DirGraph<int> InputGraph(std::istream& inp) {
  size_t vertexs;
  size_t edges;

  inp >> vertexs >> edges;

  DirGraph<int> graph;

  for (size_t i = 0; i < edges; ++i) {
    int vertex1;
    int vertex2;

    inp >> vertex1 >> vertex2;

    graph.AddEdge(vertex1 - 1, vertex2 - 1);
  }

  return graph;
}

void PrintCondGraph(std::ostream& outp, const std::vector<int>& condensated) {
  for (size_t i = 0; i < condensated.size(); ++i) {
    outp << i + 1 << " - " << condensated[i] << '\n';
  }
  outp << std::endl;
}

int main() {
  DirGraph<int> graph = InputGraph(std::cin);
  std::vector<int> condensated = Condensate(graph);
  PrintCondGraph(std::cout, condensated);
}
