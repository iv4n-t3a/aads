# Heap Class Documentation

The `Heap` class in the `Aads` namespace implements a max-heap data structure using a vector as the underlying storage. It is a template class that supports any type `T` that is comparable using the `<` operator. Below is a detailed description of the public methods, including their functionality and time complexity.

## Constructor

### `Heap()`
- **Description**: Constructs an empty max-heap.
- **Time Complexity**: O(1)
  - Initializes an empty vector, which is a constant-time operation.

## Methods

### `T& GetMax()`
### `const T& GetMax() const`
- **Description**: Returns a reference to the maximum element in the heap (the root). The const version is for read-only access.
- **Time Complexity**: O(1)
  - Directly accesses the first element of the underlying vector.

### `void Reserve(size_t size)`
- **Description**: Reserves space in the underlying vector to accommodate at least `size` elements, potentially reducing reallocation overhead during insertions.

### `size_t Size() const`
- **Description**: Returns the number of elements currently in the heap.
- **Time Complexity**: O(1)
  - Returns the size of the underlying vector, a constant-time operation.

### `void Insert(const T& new_elem)`
- **Description**: Inserts a new element into the heap, maintaining the max-heap property by sifting up the element.
- **Time Complexity**: O(log n)
  - Appends the element to the vector (O(1) amortized) and performs a sift-up operation, which takes O(log n) in the worst case, where n is the number of elements in the heap.

### `void Insert(T&& new_elem)`
- **Description**: Inserts a new element into the heap using move semantics, maintaining the max-heap property by sifting up the element.
- **Time Complexity**: O(log n)
  - Similar to the lvalue `Insert`, with the same append and sift-up operations. Move semantics may improve performance for complex types but does not affect the asymptotic complexity.

### `template <typename... Args> void Emplace(Args&&... args)`
- **Description**: Constructs a new element in-place at the end of the heap and maintains the max-heap property by sifting up the element.
- **Time Complexity**: O(log n)
  - Constructs the element directly in the vector (O(1) amortized for allocation) and performs a sift-up operation (O(log n)).

### `void ExtractMax()`
- **Description**: Removes the maximum element (root) from the heap and maintains the max-heap property by sifting down the new root.
- **Time Complexity**: O(log n)
  - Swaps the root with the last element (O(1)), removes the last element (O(1)), and performs a sift-down operation (O(log n)).

## Notes
- The heap is implemented as a max-heap, meaning the largest element is always at the root.
- All operations that modify the heap structure (Insert, Emplace, ExtractMax) maintain the max-heap property, ensuring that the parent node is always greater than or equal to its children.
- Time complexities assume that comparisons and swaps of type `T` are O(1). For complex types, the actual runtime may depend on the comparison and copy/move operations.
