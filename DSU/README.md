# Disjoint Set Union (DSU) Documentation

The `DSU` class implements a Disjoint Set Union data structure, also known as a Union-Find data structure. It is used to manage a collection of disjoint sets, supporting efficient operations to merge sets and check whether two elements belong to the same set. The implementation uses path compression and rank-based union to optimize performance.

## Public Methods

### Constructor: `DSU(size_t size)`

Initializes a DSU with `size` elements, where each element starts in its own disjoint set.

- **Parameters**:
  - `size`: The number of elements in the DSU (type: `size_t`).
- **Behavior**:
  - Creates a DSU with `size` elements, each initially in its own set.
  - Each element is its own ancestor, and the rank of each set is initialized to 0.
- **Time Complexity**: O(n), where `n` is the number of elements (`size`).
- **Memory Complexity**: O(n), for storing the ancestors and rank arrays.

### `void Unite(size_t lhs, size_t rhs)`

Merges the sets containing elements `lhs` and `rhs`.

- **Parameters**:
  - `lhs`: Index of the first element (type: `size_t`).
  - `rhs`: Index of the second element (type: `size_t`).
- **Behavior**:
  - If `lhs` and `rhs` are already in the same set, no action is taken.
  - Otherwise, the sets containing `lhs` and `rhs` are merged by attaching the root of the smaller-ranked set to the root of the larger-ranked set, updating ranks as needed.
- **Time Complexity**: O(α(n)) amortized, where `α(n)` is the inverse Ackermann function, effectively constant for practical values of `n`.
- **Memory Complexity**: O(1) additional space, excluding the internal arrays.

### `bool AreSame(size_t lhs, size_t rhs)`

Checks whether elements `lhs` and `rhs` belong to the same set.

- **Parameters**:
  - `lhs`: Index of the first element (type: `size_t`).
  - `rhs`: Index of the second element (type: `size_t`).
- **Returns**:
  - `true` if `lhs` and `rhs` are in the same set, `false` otherwise.
- **Behavior**:
  - Uses path compression to optimize future queries by making each node in the path point directly to the root.
- **Time Complexity**: O(α(n)) amortized, where `α(n)` is the inverse Ackermann function, effectively constant for practical values of `n`.
- **Memory Complexity**: O(1) additional space, excluding the internal arrays.

## Notes on Complexity

- **Time Complexity**:
  - The `Unite` and `AreSame` operations use path compression and union by rank, resulting in an amortized time complexity of O(α(n)) per operation, where `α(n)` is the inverse Ackermann function. This is nearly constant for all practical purposes, as `α(n)` grows extremely slowly and is less than 5 for any realistic `n`.
  - The constructor has a linear time complexity of O(n) due to the initialization of the internal arrays.
- **Memory Complexity**:
  - The DSU uses two internal arrays (`ancestors_` and `rank_`) of size `n`, resulting in O(n) memory usage.
  - Individual operations (`Unite` and `AreSame`) use O(1) additional space, as they only perform in-place updates.

## Usage Example

```cpp

#include "DSU/dsu.hpp"

int main() {
  Aads::DSU dsu(5);              // Initialize DSU with 5 elements
  dsu.Unite(0, 1);               // Merge sets containing elements 0 and 1
  dsu.Unite(1, 2);               // Merge sets containing elements 1 and 2
  bool same = dsu.AreSame(0, 2); // Returns true, as 0 and 2 are in the same set
}
```
