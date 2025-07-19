# PersistentArray Class Documentation

The `PersistentArray` class is a persistent data structure that maintains multiple versions of an array, allowing access to elements at specific versions and indices. Each modification creates a new version without altering previous ones, making it suitable for scenarios requiring immutable snapshots of data.

## Overview

- **Template Parameter**: `T` - The type of elements stored in the array.
- **Purpose**: Provides efficient access to and modification of elements across different versions of the array.
- **Memory Management**: The class manages memory internally, allocating arrays for nodes and leaves during construction and modifications. It ensures proper deallocation of resources in the destructor to prevent memory leaks.

## Public Methods

### Constructor

```cpp
template <std::forward_iterator Iter>
PersistentArray(Iter begin, Iter end);
```

Constructs a `PersistentArray` from a range of elements defined by forward iterators.

- **Parameters**:
  - `begin`: Iterator pointing to the start of the input range.
  - `end`: Iterator pointing to the end of the input range.
- **Time Complexity**: O(n), where n is the number of elements in the range (`std::distance(begin, end)`).
- **Memory Complexity**: O(n) for storing the initial elements and O(n) for the internal tree structure, resulting in O(n) total memory.
- **Notes**: Handles empty ranges (size 0) and single-element ranges efficiently.

### Get (Specific Version)

```cpp
const T& Get(size_t version, size_t index) const;
```

Retrieves the element at the specified `index` in the specified `version` of the array.

- **Parameters**:
  - `version`: The version of the array to query (0-based index, must be less than `Versions()`).
  - `index`: The index of the element to retrieve (must be less than `Size()`).
- **Returns**: A const reference to the element of type `T`.
- **Time Complexity**: O(log n), where n is the size of the array, due to the binary tree traversal.
- **Memory Complexity**: O(1), as no additional memory is allocated.
- **Notes**: Throws undefined behavior if `version` or `index` is out of bounds.

### Get (Latest Version)

```cpp
const T& Get(size_t index);
```

Retrieves the element at the specified `index` in the latest version of the array.

- **Parameters**:
  - `index`: The index of the element to retrieve (must be less than `Size()`).
- **Returns**: A const reference to the element of type `T`.
- **Time Complexity**: O(log n), where n is the size of the array, due to the binary tree traversal.
- **Memory Complexity**: O(1), as no additional memory is allocated.
- **Notes**: Equivalent to `Get(Versions() - 1, index)`. Throws undefined behavior if `index` is out of bounds.

### Set

```cpp
template <typename... Args>
void Set(size_t version, size_t index, Args... args);
```

Creates a new version of the array by setting the element at the specified `index` in the given `version` to a new value constructed from `args`.

- **Parameters**:
  - `version`: The version to base the new version on (must be less than `Versions()`).
  - `index`: The index of the element to modify (must be less than `Size()`).
  - `args`: Arguments forwarded to construct a new value of type `T`.
- **Time Complexity**: O(log n), where n is the size of the array, due to the creation of a new path in the tree.
- **Memory Complexity**: O(log n) for the new nodes created in the tree path, plus O(1) for the new leaf.
- **Notes**: Creates a new version, preserving the previous version unchanged. Throws undefined behavior if `version` or `index` is out of bounds.

### Versions

```cpp
size_t Versions() const;
```

Returns the number of versions of the array.

- **Returns**: The number of versions (at least 1 if the array is non-empty).
- **Time Complexity**: O(1).
- **Memory Complexity**: O(1).
- **Notes**: The initial array is version 0, and each `Set` operation increments the version count.

### Size

```cpp
size_t Size() const;
```

Returns the number of elements in the array.

- **Returns**: The size of the array, as determined by the input range during construction.
- **Time Complexity**: O(1).
- **Memory Complexity**: O(1).
- **Notes**: Returns 0 for an empty array.

## Memory Management

The `PersistentArray` class handles all memory allocation and deallocation internally. It allocates memory for the initial array and internal tree structures during construction and for new nodes during `Set` operations. The destructor ensures all allocated memory is properly freed, preventing leaks. Users do not need to manage memory manually, but should ensure valid iterator ranges and indices to avoid undefined behavior.

## Example Usage

```cpp
#include <vector>
#include <string>

#include "PersistentArray/persistent_array.hpp"

int main() {
  std::vector<int> data = {1, 2, 3, 4};
  Aads::PersistentArray<int> arr(data.begin(), data.end());

  // Access elements in initial version
  assert(arr.Get(0, 0) == 1); // Version 0, index 0
  assert(arr.Get(0, 3) == 4); // Version 0, index 3

  // Create a new version by modifying index 1
  arr.Set(0, 1, 10); // Creates version 1
  assert(arr.Get(1, 1) == 10); // Version 1, index 1
  assert(arr.Get(0, 1) == 2);  // Version 0 unchanged

  // Use latest version
  assert(arr.Get(1) == 10); // Latest version (1), index 1
  assert(arr.Versions() == 2);
  assert(arr.Size() == 4);

  // Works with non-integer types
  std::vector<std::string> strings = {"a", "b", "c"};
  Aads::PersistentArray<std::string> str_arr(strings.begin(), strings.end());
  str_arr.Set(0, 1, std::string("new"));
  assert(str_arr.Get(1, 1) == "new");
}
```

## Notes

- The class assumes valid input ranges and indices. Out-of-bounds access leads to undefined behavior.
- The persistent nature ensures that modifications create new versions without affecting previous ones, making it ideal for versioned data storage.
- The implementation uses a binary tree internally, which contributes to the logarithmic time complexity for `Get` and `Set` operations.


