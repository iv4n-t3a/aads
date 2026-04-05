# Kruskal's Algorithm for Minimum Spanning Tree

Finds the minimum spanning tree (MST) of a weighted undirected graph using a greedy approach with Disjoint Set Union (DSU).

## Algorithm Idea

Kruskal's algorithm builds the MST by:
1. Sorting all edges by weight in ascending order
2. Iterating through sorted edges and adding each edge to the MST if it doesn't create a cycle
3. Using DSU to efficiently check for cycles and unite components

The algorithm is greedy: it always picks the minimum weight edge that doesn't create a cycle. This greedy choice is optimal due to the cut property of MSTs.

## Complexity

* **Time**: `O(|E| log |E|)` where `|E|` is the number of edges
  - Sorting edges: `O(|E| log |E|)`
  - DSU operations: `O(|E| α(|V|))` where α is the inverse Ackermann function (effectively constant)
* **Space**: `O(|V|)` for DSU structure

## Classes and Functions

### `Aads::DSU`

Disjoint Set Union data structure with path compression and union by rank.

**Constructor:**
```cpp
DSU(size_t size)
```
Creates DSU for `size` elements (0 to size-1).

**Methods:**
- `void Unite(size_t lhs, size_t rhs)`: Unites sets containing `lhs` and `rhs`
- `bool AreSame(size_t lhs, size_t rhs)`: Checks if elements are in the same set

**Time complexity:** Both operations are `O(α(n))` amortized (effectively constant)

### `Aads::Edge`

Represents a weighted edge.

**Fields:**
- `int from`: Source vertex
- `int to`: Destination vertex
- `int weight`: Edge weight

**Operators:**
- `bool operator<(const Edge& other) const`: Compares edges by weight

### `Aads::Kruskal(int vertex_count, std::vector<Edge>& edges)`

Finds the minimum spanning tree weight.

**Parameters:**
- `vertex_count`: Number of vertices in the graph
- `edges`: Vector of edges (will be sorted)

**Returns:**
- `int`: Total weight of the minimum spanning tree

**Time complexity:** `O(|E| log |E|)`

## Usage Example

```cpp
#include "Kruskal/kruskal.hpp"

std::vector<Aads::Edge> edges = {
    {0, 1, 4},
    {0, 2, 3},
    {1, 2, 1},
    {1, 3, 2},
    {2, 3, 5}
};

int mst_weight = Aads::Kruskal(4, edges);
// mst_weight = 6 (edges: 1-2 weight 1, 1-3 weight 2, 0-2 weight 3)
```
