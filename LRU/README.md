# LRU Cache Documentation

This document provides an overview of the `Aads::LruCache` class, a templated C++ implementation of a Least Recently Used (LRU) cache. The cache stores key-value pairs with a fixed capacity, evicting the least recently used item when the capacity is exceeded.

## Overview

The `Aads::LruCache` class is a generic implementation that supports any key type `K` and value type `T`. It uses a combination of a doubly-linked list and an unordered map to achieve O(1) time complexity for most operations. The doubly-linked list maintains the order of elements based on their usage, while the unordered map provides fast key-based access to the nodes.

## Class Definition

The `Aads::LruCache` class is templated with two parameters:
- `K`: The type of the key.
- `T`: The type of the value.

### Constructor
```cpp
LruCache(size_t size_limit)
```
- **Purpose**: Initializes the cache with a specified maximum size.
- **Parameters**:
  - `size_limit`: The maximum number of key-value pairs the cache can hold.
- **Behavior**: Sets the internal size limit for the cache.

### Public Methods

#### Operator `[]`
```cpp
T& operator[](const K& key)
```
- **Purpose**: Retrieves or creates a value associated with the given key, marking it as most recently used.
- **Parameters**:
  - `key`: The key to access or insert.
- **Returns**: A reference to the value associated with the key.
- **Behavior**:
  - If the key exists, moves the corresponding node to the most recently used position and returns its value.
  - If the key does not exist, creates a new node with a default-constructed value, adds it to the cache as the most recently used, and returns its value.
  - If the cache exceeds its size limit, removes the least recently used item.

#### GetWithoutUse
```cpp
T& GetWithoutUse(const K& key)
```
- **Purpose**: Retrieves the value associated with a key without updating its usage status.
- **Parameters**:
  - `key`: The key to look up.
- **Returns**: A reference to the value associated with the key.
- **Throws**: `std::out_of_range` if the key is not found.
- **Behavior**: Provides read-only access to the value without affecting the LRU order.

#### Contains
```cpp
bool Contains(const K& key) const
```
- **Purpose**: Checks if a key exists in the cache.
- **Parameters**:
  - `key`: The key to check.
- **Returns**: `true` if the key exists, `false` otherwise.
- **Behavior**: Performs a constant-time lookup using the internal map.

#### RemoveLeastUsed
```cpp
void RemoveLeastUsed()
```
- **Purpose**: Removes the least recently used item from the cache.
- **Behavior**:
  - Updates the doubly-linked list to remove the least recently used node.
  - Erases the corresponding key from the map.
  - Adjusts pointers to maintain the list structure.

#### Remove
```cpp
void Remove(const K& key)
```
- **Purpose**: Removes a specific key-value pair from the cache.
- **Parameters**:
  - `key`: The key to remove.
- **Behavior**:
  - Moves the node to the least recently used position.
  - Calls `RemoveLeastUsed` to remove it from the cache.

#### Use
```cpp
void Use(const K& key)
```
- **Purpose**: Marks a key as recently used, moving it to the most recently used position.
- **Parameters**:
  - `key`: The key to mark as recently used.
- **Behavior**:
  - Updates the doubly-linked list to move the node to the most recently used position.
  - Does nothing if the key is already the most recently used.

#### Size
```cpp
size_t Size() const
```
- **Purpose**: Returns the current number of items in the cache.
- **Returns**: The number of key-value pairs in the cache.
- **Behavior**: Queries the size of the internal map.

#### UpdateLimit
```cpp
void UpdateLimit(size_t new_limit)
```
- **Purpose**: Updates the cache's size limit, removing least recently used items if necessary.
- **Parameters**:
  - `new_limit`: The new maximum size of the cache.
- **Behavior**:
  - If the new limit is smaller than the current size, removes least recently used items until the size is within the new limit.
  - Updates the internal size limit.

## Usage Example
```cpp
#include <iostream>
#include <string>
#include "LRU/lru.hpp"

int main() {
    Aads::LruCache<std::string, int> cache(2); // Cache with size limit of 2

    cache["a"] = 1; // Add key "a" with value 1
    cache["b"] = 2; // Add key "b" with value 2
    std::cout << cache["a"] << std::endl; // Access "a", making it most recently used
    cache["c"] = 3; // Add "c", evicting "b" (least recently used)

    if (!cache.Contains("b")) {
        std::cout << "Key 'b' was evicted" << std::endl;
    }

    cache.UpdateLimit(1); // Reduce limit to 1, evicting least recently used ("a")
    std::cout << cache["c"] << std::endl; // Access "c"
}
```

## Time Complexity
- **Access (`operator[]`)**: O(1)
- **GetWithoutUse**: O(1)
- **Contains**: O(1)
- **RemoveLeastUsed**: O(1)
- **Remove**: O(1)
- **Use**: O(1)
- **Size**: O(1)
- **UpdateLimit**: O(n) in the worst case, where n is the number of items to remove.

## Space Complexity
- **Overall**: O(n), where n is the number of key-value pairs stored.
- **Per Node**: Each node stores a key, value, and two pointers.
- **Map**: The unordered map stores key-to-node mappings.

## Notes
- The cache assumes that keys are unique and that the key type `K` is hashable for use in `std::unordered_map`.
- The value type `T` must be default-constructible for the `operator[]` to work when inserting new keys.
- The implementation is not thread-safe; external synchronization is required for concurrent access.
- The cache maintains the LRU order using a doubly-linked list, ensuring O(1) updates for usage tracking.
