# Kuhn's Algorithm for Maximum Matching

Finds maximum matching in a bipartite graph using augmenting paths.

## Algorithm Idea

Kuhn's algorithm (also known as the Hungarian algorithm for bipartite matching) finds a maximum matching by iteratively searching for augmenting paths. An augmenting path is a path that starts and ends at unmatched vertices, alternating between non-matching and matching edges. Each augmenting path increases the matching size by 1. The algorithm terminates when no more augmenting paths exist.

## Complexity

* **Time**: `O(|V| × |E|)` where `|V|` is the number of vertices and `|E|` is the number of edges
* **Space**: `O(|V|)`

In practice, often performs much better than worst-case complexity.

## Classes and Functions

### `Aads::AbstractGraph<T, E, bool is_directed>`

Abstract base class for graph implementations.

**Methods:**
- `virtual size_t CountVertices() const`
- `virtual size_t CountEdges() const`
- `virtual void AddEdge(EdgeT edge)`
- `virtual std::span<const EdgeT> GetAdj(VertexT vertex) const`

### `Aads::GraphImpl<T, E, bool is_directed, Hash>`

Concrete graph implementation using adjacency lists.

### `Aads::AbstractBipartGraph<T, E>`

Abstract interface for bipartite graphs.

**Methods:**
- `virtual std::span<const VertexT> LeftPart() const`: Returns vertices in left partition
- `virtual void AddVertexToLeft(VertexT vertex)`: Adds vertex to left partition

### `Aads::BipartGraphImpl<T, E, bool is_directed, Hash>`

Bipartite graph implementation combining graph and bipartite interfaces.

### `Aads::FindMaxMatching<BipartitionGraph, Vertex, VertexHash>(const BipartitionGraph& graph)`

Finds maximum matching in a bipartite graph.

**Parameters:**
- `graph`: Bipartite graph

**Returns:**
- `std::unordered_map<Vertex, Vertex, VertexHash>`: Matching as map from right vertices to left vertices

**Time complexity:** `O(|V| × |E|)`

### Helper Types

**`Aads::Vertex`**
- Represents a vertex in bipartite graph
- Fields: `size_t index`, `bool is_right`

**`Aads::VertexHash`**
- Hash function for `Vertex` type

**`Aads::GraphT`**
- Type alias for `BipartGraphImpl<Vertex, std::pair<Vertex, Vertex>, false, VertexHash>`

## Usage Example

```cpp
#include "Khun/khun.hpp"

Aads::GraphT graph;

// Add left vertices
graph.AddVertexToLeft({0, false});
graph.AddVertexToLeft({1, false});

// Add edges from left to right
graph.AddEdge({{0, false}, {0, true}});
graph.AddEdge({{0, false}, {1, true}});
graph.AddEdge({{1, false}, {1, true}});

auto matching = Aads::FindMaxMatching<Aads::GraphT, Aads::Vertex, Aads::VertexHash>(graph);
// matching.size() gives the size of maximum matching
```
