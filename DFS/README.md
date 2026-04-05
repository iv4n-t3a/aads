# Depth-First Search (DFS) with Connected Components

Generic DFS implementation using visitor pattern to find connected components in an undirected graph.

## Algorithm Idea

DFS explores a graph by going as deep as possible along each branch before backtracking. The visitor pattern allows customizing behavior at key points (explore, leave, edges). For connected components, DFS is run from each unvisited vertex, grouping all reachable vertices into the same component.

## Complexity

* **Time**: `O(|V| + |E|)` where `|V|` is the number of vertices and `|E|` is the number of edges
* **Space**: `O(|V|)` for visited tracking

## Classes and Functions

### `Aads::Graph<T, bool is_directed = false>`

Template class representing a graph with adjacency list.

**Methods:**
- `void AddEdge(VertexT from, VertexT to)`: Adds an edge to the graph
- `std::span<const VertexT> GetAdj(VertexT vertex) const`: Returns adjacent vertices
- `size_t CountVertexs() const`: Returns number of vertices
- `size_t CountEdges() const`: Returns number of edges

### `Aads::DFS(const Graph& graph, const Vertex& vertex, Visitor& visitor)`

Generic DFS traversal function using visitor pattern.

**Parameters:**
- `graph`: The graph to traverse
- `vertex`: Starting vertex
- `visitor`: Visitor object implementing the visitor interface

### `Aads::Visitor<Vertex>`

Default visitor implementation for DFS.

**Methods:**
- `void Explore(Vertex vertex)`: Called when vertex is first visited
- `void Leave(Vertex vertex)`: Called when leaving vertex
- `bool IsVisited(Vertex vertex) const`: Checks if vertex was visited
- `std::unordered_set<Vertex> GetVisited()`: Returns all visited vertices

### `Aads::FindComps(const Graph<int>& graph)`

Finds all connected components in an undirected graph.

**Returns:**
- `std::vector<std::vector<int>>`: Vector of components, each containing vertex indices

**Time complexity:** `O(|V| + |E|)`

## Usage Example

```cpp
#include "DFS/dfs.hpp"

Aads::Graph<int> graph;
graph.AddEdge(0, 1);
graph.AddEdge(1, 2);
graph.AddEdge(3, 4);

// Find connected components
auto components = Aads::FindComps(graph);
// components[0] = {0, 1, 2}
// components[1] = {3, 4}

// Or use DFS with custom visitor
Aads::Visitor<int> visitor;
Aads::DFS(graph, 0, visitor);
```
