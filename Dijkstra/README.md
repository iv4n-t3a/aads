# Dijkstra's Shortest Path Algorithm

Finds shortest paths from a source vertex to all other vertices in a weighted graph with non-negative edge weights.

## Algorithm Idea

Dijkstra's algorithm maintains a priority queue of vertices ordered by their tentative distance from the source. It repeatedly extracts the vertex with minimum distance, relaxes its outgoing edges, and updates distances to neighbors. The algorithm guarantees optimal paths because it processes vertices in order of increasing distance.

## Complexity

* **Time**: `O((|V| + |E|) log |V|)` using binary heap priority queue
* **Space**: `O(|V|)` for distance and visited tracking

Where `|V|` is the number of vertices and `|E|` is the number of edges.

## Classes and Functions

### `Aads::Edge<T>`

Represents a weighted edge in the graph.

**Constructor:**
```cpp
Edge(T from, T to, int weight)
```

**Public Fields:**
- `T from`: Source vertex
- `T to`: Destination vertex
- `int weight`: Edge weight

### `Aads::Graph<T>`

Template class representing a weighted graph.

**Methods:**
- `void SetVerticesCount(size_t count)`: Sets the number of vertices
- `void AddEdge(Edge<T> edge)`: Adds a weighted edge (automatically adds reverse edge for undirected graph)
- `std::span<const EdgeT> GetAdj(VertexT vertex) const`: Returns adjacent edges
- `size_t CountVertices() const`: Returns number of vertices
- `size_t CountEdges() const`: Returns number of edges

### `Aads::Dijkstra(const Graph& graph, const Vertex& start, Visitor& vis)`

Runs Dijkstra's algorithm from a starting vertex.

**Parameters:**
- `graph`: The weighted graph
- `start`: Starting vertex
- `vis`: Visitor object that tracks distances

**Time complexity:** `O((|V| + |E|) log |V|)`

### `Aads::Visitor<Vertex>`

Visitor class that tracks shortest distances.

**Methods:**
- `void SetDist(const Vertex& vert, int dist)`: Sets distance to vertex
- `int GetDistance(const Vertex& vert) const`: Gets distance to vertex (returns `kInfinity` if unreachable)
- `bool IsProcessed(const Vertex& vert)`: Checks if vertex has been processed

**Constants:**
- `kInfinity = 2009000999`: Represents unreachable vertices

## Usage Example

```cpp
#include "Dijkstra/dijkstra.hpp"

Aads::Graph<int> graph;
graph.SetVerticesCount(4);
graph.AddEdge(Aads::Edge<int>(0, 1, 10));
graph.AddEdge(Aads::Edge<int>(0, 2, 5));
graph.AddEdge(Aads::Edge<int>(2, 1, 3));
graph.AddEdge(Aads::Edge<int>(1, 3, 1));

Aads::Visitor<int> vis;
Aads::Dijkstra(graph, 0, vis);

int dist_to_3 = vis.GetDistance(3);  // Shortest distance from 0 to 3
```
