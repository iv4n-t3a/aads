# Kosaraju's Algorithm for Strongly Connected Components

Finds all strongly connected components (SCCs) in a directed graph and builds the condensation graph.

## Algorithm Idea

Kosaraju's algorithm uses two DFS passes:
1. **First pass**: Run DFS on the original graph to compute finish times (t_out) for all vertices
2. **Second pass**: Run DFS on the transposed graph in decreasing order of finish times

Each DFS tree in the second pass corresponds to one strongly connected component. Vertices are assigned component numbers based on which DFS tree they belong to.

## Complexity

* **Time**: `O(|V| + |E|)` where `|V|` is the number of vertices and `|E|` is the number of edges
* **Space**: `O(|V| + |E|)` for storing graph and transpose

## Classes and Functions

### `Aads::Graph<T, bool IsDirected = false>`

Template class representing a graph with adjacency list.

**Methods:**
- `void AddEdge(VertexT from, VertexT to)`: Adds a directed edge
- `std::span<const VertexT> GetAdj(VertexT vertex) const`: Returns adjacent vertices
- `size_t CountVertexs() const`: Returns number of vertices
- `size_t CountEdges() const`: Returns number of edges

### `Aads::DirGraph<T>`

Type alias for directed graph: `Graph<T, true>`

### `Aads::Transponed(const DirGraph<T>& graph)`

Creates the transpose (reverse) of a directed graph.

**Returns:**
- `DirGraph<T>`: Graph with all edges reversed

**Time complexity:** `O(|V| + |E|)`

### `Aads::Condensate(const DirGraph<int>& graph)`

Finds strongly connected components and assigns component numbers.

**Returns:**
- `std::vector<int>`: Vector where `result[i]` is the component number of vertex `i`

**Time complexity:** `O(|V| + |E|)`

### Helper Classes

**`Aads::TOutVisitor<Vertex>`**
- DFS visitor that computes finish times (t_out)

**`Aads::Visitor<Vertex>`**
- Basic DFS visitor for marking visited vertices

## Usage Example

```cpp
#include "Kosaraju/kosaraju.hpp"

Aads::DirGraph<int> graph;
graph.AddEdge(0, 1);
graph.AddEdge(1, 2);
graph.AddEdge(2, 0);
graph.AddEdge(1, 3);
graph.AddEdge(3, 4);
graph.AddEdge(4, 3);

auto condensated = Aads::Condensate(graph);
// condensated[0] == condensated[1] == condensated[2] (same SCC)
// condensated[3] == condensated[4] (same SCC)
// condensated[0] != condensated[3] (different SCCs)
```
