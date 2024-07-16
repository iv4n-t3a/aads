#include <iostream>
#include <unordered_set>
#include <vector>

template <typename Visitor>
void DFSHelper(const std::vector<std::vector<int>>& adj, Visitor& visitor,
               int from, int ancestor = -1) {
  visitor.Explore(from);

  for (int to : adj[from]) {
    if (to == ancestor) {
      continue;
    }

    if (visitor.IsVisited(to)) {
      visitor.BackEdge(from, to);
    } else {
      DFSHelper(adj, visitor, to);
      visitor.TreeEdge(from, to);
    }
  }

  visitor.Leave(from);
}

template <typename Visitor>
void DFS(const std::vector<std::vector<int>>& adj, Visitor& visitor, int from) {
  visitor.Init(from);
  DFSHelper(adj, visitor, from);
}

class CutPointsSearchVisitor {
 public:
  CutPointsSearchVisitor(int nodes)
      : visited_(nodes), t_in_(nodes), t_up_(nodes), children_(nodes) {}

  bool IsVisited(int node) { return visited_[node]; }

  void Init(int node) { root_ = node; }

  void Explore(int node) {
    t_in_[node] = t_up_[node] = timer_++;
    visited_[node] = true;
  }

  void Leave(int node) {
    if (node == root_ and children_[node] > 1) {
      cutpoints_.insert(node);
    }
  }

  void BackEdge(int from, int to) {
    t_up_[from] = std::min(t_up_[from], t_in_[to]);
  }

  void TreeEdge(int from, int to) {
    t_up_[from] = std::min(t_up_[from], t_up_[to]);
    children_[from] += 1;

    if (t_up_[to] >= t_in_[from] and from != root_) {
      cutpoints_.insert(from);
    }
  }

  std::unordered_set<int> GetCutpoints() { return cutpoints_; }

 private:
  int root_ = -1;
  int timer_ = 0;
  std::vector<bool> visited_;
  std::vector<int> t_in_;
  std::vector<int> t_up_;
  std::vector<int> children_;
  std::unordered_set<int> cutpoints_;
};

std::unordered_set<int> CutPoints(const std::vector<std::vector<int>>& adj) {
  CutPointsSearchVisitor visitor(adj.size());

  for (size_t i = 0; i < adj.size(); ++i) {
    if (visitor.IsVisited(i)) {
      continue;
    }
    DFS(adj, visitor, i);
  }

  return visitor.GetCutpoints();
}

int main() {
  size_t nodes;
  size_t edges;

  std::cin >> nodes >> edges;

  std::vector<std::vector<int>> adj(nodes);

  for (size_t i = 0; i < edges; ++i) {
    int node1;
    int node2;

    std::cin >> node1 >> node2;
    adj[node1 - 1].push_back(node2 - 1);
    adj[node2 - 1].push_back(node1 - 1);
  }

  std::unordered_set<int> cut_points = CutPoints(adj);

  for (int node : cut_points) {
    std::cout << node + 1 << ' ';
  }
  std::cout << std::endl;
}
