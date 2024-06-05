#include <iostream>
#include <queue>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
class Edge {
 public:
  Edge(T from, T to, int weight) : from(from), to(to), weight(weight) {}

  T from;
  T to;
  int weight;
};

template <typename T>
class Graph {
 public:
  using VertexT = T;
  using EdgeT = Edge<T>;

  void SetVerticesCount(size_t count) {
    vertexcount_ = std::max(count, vertexcount_);
  }

  size_t CountVertices() const { return vertexcount_; }
  size_t CountEdges() const { return edgecount_; }

  void AddEdge(Edge<T> edge) {
    edgecount_ += 1;

    if (not adj_.contains(edge.from)) {
      adj_[edge.from] = {};
    }
    if (not adj_.contains(edge.to)) {
      adj_[edge.to] = {};
    }

    adj_[edge.from].push_back(edge);
    adj_[edge.to].push_back(Edge<T>(edge.to, edge.from, edge.weight));
    vertexcount_ = std::max(vertexcount_, adj_.size());
  }

  std::span<const EdgeT> GetAdj(VertexT vertex) const {
    if (not adj_.contains(vertex)) {
      return std::span<const EdgeT>();
    }
    return std::span(adj_.at(vertex));
  }

 private:
  size_t vertexcount_ = 0;
  size_t edgecount_ = 0;
  std::unordered_map<VertexT, std::vector<EdgeT>> adj_;
};

template <typename Graph, typename Vertex, typename Visitor>
void Dijkstra(const Graph& graph, const Vertex& start, Visitor& vis) {
  std::priority_queue<std::pair<int, Vertex>> queue;

  queue.push({0, start});
  vis.SetDist(start, 0);

  while (not queue.empty()) {
    int dist = -queue.top().first;
    Vertex vertex = queue.top().second;
    queue.pop();

    if (vis.IsProcessed(vertex)) {
      continue;
    }
    vis.ExamineVertex(vertex);

    for (Edge<Vertex> edge : graph.GetAdj(vertex)) {
      if (dist + edge.weight < vis.GetDistance(edge.to)) {
        vis.SetDist(edge.to, dist + edge.weight);
        queue.push({-dist - edge.weight, edge.to});
      }
    }
  }
}

const int kInfinity = 2009000999;

template <typename Vertex>
class Visitor {
 public:
  void ExamineVertex(const Vertex& vert) { processed_.insert(vert); }

  bool IsProcessed(const Vertex& vert) { return processed_.contains(vert); }

  void SetDist(const Vertex& vert, int dist) { distance_[vert] = dist; }

  int GetDistance(const Vertex& vert) const {
    if (not distance_.contains(vert)) {
      return kInfinity;
    }
    return distance_.at(vert);
  }

 private:
  std::unordered_map<Vertex, int> distance_;
  std::unordered_set<Vertex> processed_;
};

Graph<int> InputGraph(std::istream& inp) {
  size_t vertices;
  size_t edges;

  inp >> vertices >> edges;

  Graph<int> graph;
  graph.SetVerticesCount(vertices);

  for (size_t i = 0; i < edges; ++i) {
    int vertex1;
    int vertex2;
    int weight;

    inp >> vertex1 >> vertex2 >> weight;

    graph.AddEdge(Edge<int>(vertex1, vertex2, weight));
  }

  return graph;
}

template <typename Visitor>
void PrintDistances(const Visitor& vis, size_t vertices, std::ostream& outp) {
  for (size_t i = 0; i < vertices; ++i) {
    outp << vis.GetDistance(i) << " ";
  }
  outp << std::endl;
}

void Runtest(std::istream& inp, std::ostream& outp) {
  Graph<int> graph = InputGraph(inp);

  int start;
  inp >> start;

  Visitor<int> vis;
  Dijkstra(graph, start, vis);

  PrintDistances(vis, graph.CountVertices(), outp);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t tests;
  std::cin >> tests;

  for (size_t i = 0; i < tests; ++i) {
    Runtest(std::cin, std::cout);
  }
}
