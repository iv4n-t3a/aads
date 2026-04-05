# Articulation Points (Cut Vertices) Algorithm

Finds all articulation points (cut vertices) in an undirected graph using DFS with timestamps.

## Algorithm Idea

An articulation point is a vertex whose removal increases the number of connected components. The algorithm uses DFS to compute entry times (`t_in`) and lowest reachable times (`t_up`). A vertex `u` is an articulation point if:
1. It's the root of DFS tree and has more than one child, OR
2. It has a child `v` where `t_up[v] >= t_in[u]` (meaning `v` cannot reach ancestors of `u` without going through `u`)

## Complexity

* **Time**: `O(|V| + |E|)` where `|V|` is the number of vertices and `|E|` is the number of edges
* **Space**: `O(|V|)`

## Functions and Classes

### `Aads::CutPoints(const std::vector<std::vector<int>>& adj)`

Finds all articulation points in an undirected graph.

**Parameters:**
- `adj`: Adjacency list representation of the graph

**Returns:**
- `std::unordered_set<int>`: Set of articulation point vertex indices

**Time complexity:** `O(|V| + |E|)`

### Helper Classes

**`Aads::CutPointsSearchVisitor`**
- DFS visitor that tracks timestamps and identifies articulation points
- Handles special case for root vertices

**`Aads::DFS` and `Aads::DFSHelper`**
- Generic DFS traversal templates that work with visitor pattern

## Usage Example

```cpp
#include "CutPoints/cut_points.hpp"

// Create adjacency list for graph with 5 vertices
std::vector<std::vector<int>> adj(5);
adj[0].push_back(1);
adj[1].push_back(0);
adj[1].push_back(2);
adj[2].push_back(1);
adj[2].push_back(3);
adj[3].push_back(2);
adj[3].push_back(4);
adj[4].push_back(3);

auto cut_points = Aads::CutPoints(adj);
// cut_points contains indices of all articulation points
```
