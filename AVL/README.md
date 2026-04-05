# AVL Tree

Self-balancing binary search tree that maintains height balance through rotations.

## Algorithm Idea

AVL tree maintains the invariant that for every node, the heights of its left and right subtrees differ by at most 1. When this balance is violated after insertion, the tree performs rotations (single or double) to restore balance. This ensures logarithmic height and efficient operations.

## Complexity

* **Insert**: `O(log n)`
* **Contains**: `O(log n)`
* **Next (successor search)**: `O(log n)`

## Classes and Methods

### `Aads::Tree<T>`

Template class implementing an AVL tree for any comparable type `T`.

#### Public Methods

**`bool Contains(T value)`**
- Checks if a value exists in the tree
- Returns `true` if found, `false` otherwise
- Time complexity: `O(log n)`

**`bool ContainsNext(T value)`**
- Checks if there exists an element greater than or equal to `value`
- Returns `true` if such element exists
- Time complexity: `O(log n)`

**`T Next(T value)`**
- Finds the smallest element greater than or equal to `value`
- Precondition: `ContainsNext(value)` must be `true`
- Time complexity: `O(log n)`

**`void Insert(T value)`**
- Inserts a value into the tree
- If value already exists, does nothing
- Automatically rebalances the tree
- Time complexity: `O(log n)`

## Usage Example

```cpp
#include "AVL/avl.hpp"

Aads::Tree<int> tree;
tree.Insert(5);
tree.Insert(3);
tree.Insert(7);

if (tree.Contains(5)) {
    // Element found
}

if (tree.ContainsNext(4)) {
    int next = tree.Next(4);  // Returns 5
}
```
