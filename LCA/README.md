# Lowest Common Ancestor (LCA) with Sparse Table

Finds the lowest common ancestor of two vertices in a rooted tree and computes distances between vertices.

## Algorithm Idea

The algorithm uses Euler tour of the tree combined with Range Minimum Query (RMQ):
1. **Euler tour**: Perform DFS recording each vertex visit (including returns from children)
2. **Depth tracking**: Record depth of each vertex and first occurrence in Euler tour
3. **Sparse Table**: Build RMQ structure on Euler tour to find vertex with minimum depth
4. **LCA query**: LCA of vertices u and v is the vertex with minimum depth between their first occurrences in Euler tour

Distance between vertices is computed as: `depth[u] + depth[v] - 2 * depth[LCA(u,v)]`

## Complexity

* **Preprocessing**: `O(n log n)` where `n` is the number of vertices
* **LCA query**: `O(1)`
* **Distance query**: `O(1)`
* **Space**: `O(n log n)`

## Classes and Functions

### `Aads::SparseTable<T>`

Generic sparse table for Range Minimum Query with any associative function.

**Constructor:**
```cpp
template <typename Iter>
SparseTable(Iter begin, Iter end, std::function<T(T, T)> func)
```

**Methods:**
- `int Calc(size_t left, size_t right) const`: Computes function result on range [left, right]

**Time complexity:** `O(1)` per query after `O(n log n)` preprocessing

### `Aads::Graph<T, bool is_directed = false>`

Template class representing a graph with adjacency list.

**Methods:**
- `void AddEdge(VertexT from, VertexT to)`: Adds an edge
- `std::span<const VertexT> GetAdj(VertexT vertex) const`: Returns adjacent vertices
- `size_t CountVertexs() const`: Returns number of vertices
- `size_t CountEdges() const`: Returns number of edges

### `Aads::LCA<Graph, Vertex>`

LCA data structure for a rooted tree.

**Constructor:**
```cpp
LCA(const Graph& graph, Vertex root)
```
Preprocesses the tree rooted at `root`.

**Methods:**
- `Vertex GetLca(Vertex vert1, Vertex vert2) const`: Returns LCA of two vertices
- `int Depth(Vertex vert) const`: Returns depth of a vertex from root

**Time complexity:** 
- Constructor: `O(n log n)`
- Queries: `O(1)`

## Usage Example

```cpp
#include "LCA/lca.hpp"

Aads::Graph<int> tree;
tree.AddEdge(0, 1);
tree.AddEdge(0, 2);
tree.AddEdge(1, 3);
tree.AddEdge(1, 4);

Aads::LCA<Aads::Graph<int>, int> lca(tree, 0);  // Root at vertex 0

int ancestor = lca.GetLca(3, 4);  // Returns 1
int distance = lca.Depth(3) + lca.Depth(4) - 2 * lca.Depth(ancestor);
```
