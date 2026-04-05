# Bridge Finding Algorithm

Finds all bridges (cut edges) in an undirected graph using DFS with timestamps.

## Algorithm Idea

A bridge is an edge whose removal increases the number of connected components. The algorithm uses DFS to compute entry times (`t_in`) and lowest reachable times (`t_up`) for each vertex. An edge `(u, v)` is a bridge if `t_up[v] >= t_in[v]`, meaning vertex `v` cannot reach any ancestor of `u` without using edge `(u, v)`.

## Complexity

* **Time**: `O(|V| + |E|)` where `|V|` is the number of vertices and `|E|` is the number of edges
* **Space**: `O(|V|)`

## Functions and Classes

### `Aads::Bridges(const std::vector<std::vector<int>>& adj)`

Finds all bridges in an undirected graph.

**Parameters:**
- `adj`: Adjacency list representation of the graph

**Returns:**
- `std::vector<std::pair<int, int>>`: List of bridges as pairs of vertex indices

**Time complexity:** `O(|V| + |E|)`

### Helper Classes

**`Aads::BridgeSearchVisitor`**
- DFS visitor that tracks timestamps and identifies bridges
- Used internally by the `Bridges` function

**`Aads::DFS` and `Aads::DFSHelper`**
- Generic DFS traversal templates that work with visitor pattern

## Usage Example

```cpp
#include "Bridges/bridges.hpp"

// Create adjacency list for graph with 4 vertices
std::vector<std::vector<int>> adj(4);
adj[0].push_back(1);
adj[1].push_back(0);
adj[1].push_back(2);
adj[2].push_back(1);
adj[2].push_back(3);
adj[3].push_back(2);

auto bridges = Aads::Bridges(adj);
// bridges contains all bridge edges
```
