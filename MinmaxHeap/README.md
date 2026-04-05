# Min-Max Heap

A double-ended priority queue that efficiently supports both minimum and maximum operations.

## Algorithm Idea

Min-max heap is a complete binary tree where levels alternate between min-levels and max-levels:
- **Min-levels** (even depth): each node is smaller than all its descendants
- **Max-levels** (odd depth): each node is larger than all its descendants

This structure allows `O(1)` access to both minimum and maximum elements. Insertions and deletions use specialized sift-up and sift-down operations that respect the min-max property, checking both parent and grandparent relationships.

## Complexity

* **Insert**: `O(log n)`
* **Extract Min/Max**: `O(log n)`
* **Get Min/Max**: `O(1)`
* **Size**: `O(1)`
* **Clear**: `O(1)`

## Classes and Functions

### `Aads::MinMaxHeap<T>`

Template class implementing a min-max heap for any comparable type `T`.

#### Constructor
```cpp
MinMaxHeap()
```
Creates an empty min-max heap.

#### Public Methods

**`T& GetMin()`** / **`const T& GetMin() const`**
- Returns reference to the minimum element
- Precondition: heap is not empty
- Time complexity: `O(1)`

**`T& GetMax()`** / **`const T& GetMax() const`**
- Returns reference to the maximum element
- Precondition: heap is not empty
- Time complexity: `O(1)`

**`size_t Size() const`**
- Returns the number of elements in the heap
- Time complexity: `O(1)`

**`void Clear()`**
- Removes all elements from the heap
- Time complexity: `O(1)`

**`void Insert(const T& new_elem)`** / **`void Insert(T&& new_elem)`**
- Inserts an element into the heap
- Time complexity: `O(log n)`

**`template <typename... Args> void Emplace(Args&&... args)`**
- Constructs and inserts an element in-place
- Time complexity: `O(log n)`

**`void ExtractMin()`**
- Removes the minimum element
- Precondition: heap is not empty
- Time complexity: `O(log n)`

**`void ExtractMax()`**
- Removes the maximum element
- Precondition: heap is not empty
- Time complexity: `O(log n)`

## Usage Example

```cpp
#include "MinmaxHeap/minmax_heap.hpp"

Aads::MinMaxHeap<int> heap;

heap.Insert(5);
heap.Insert(3);
heap.Insert(7);
heap.Insert(1);
heap.Insert(9);

int min = heap.GetMin();  // Returns 1
int max = heap.GetMax();  // Returns 9

heap.ExtractMin();  // Removes 1
heap.ExtractMax();  // Removes 9

// Now min is 3, max is 7
```

## Helper Functions

### `Aads::Log2(uint32_t num)`

Computes floor(log2(num)) efficiently using bit operations.

**Time complexity:** `O(1)`
