# TimSort

Adaptive, stable sorting algorithm that combines merge sort and insertion sort, optimized for real-world data.

## Algorithm Idea

TimSort exploits existing order in data by:
1. **Finding runs**: Identifies naturally occurring sorted sequences (runs) in the input
2. **Minimum run size**: Ensures runs are at least a minimum size using insertion sort
3. **Merging**: Merges runs using a stack-based approach with galloping mode for efficiency
4. **Adaptive**: Performs better on partially sorted data

The algorithm maintains a stack of runs and merges them according to invariants that ensure balanced merge tree, achieving `O(n log n)` worst-case while being `O(n)` on already sorted data.

## Complexity

* **Best case**: `O(n)` when data is already sorted
* **Average case**: `O(n log n)`
* **Worst case**: `O(n log n)`
* **Space**: `O(n)` auxiliary space for merging
* **Stability**: Stable (preserves relative order of equal elements)

## Functions

### `Aads::TimSort(Iter begin, Iter end)`

Sorts elements in range [begin, end) using TimSort algorithm.

**Template Parameters:**
- `Iter`: Random access iterator type

**Parameters:**
- `begin`: Iterator to the beginning of the range
- `end`: Iterator to the end of the range

**Requirements:**
- Iterator must be random access
- Elements must be comparable with `operator<`

**Time complexity:** `O(n log n)` worst case, `O(n)` best case

### Helper Functions

**`Aads::CalcMinRun(size_t size)`**
- Calculates optimal minimum run size for given array size
- Returns value between 32 and 64

**`Aads::InsertionSort(Iter begin, Iter end)`**
- Sorts small ranges using insertion sort
- Used for runs smaller than minrun

**`Aads::Merge(Iter begin, Iter mid, Iter end, ValType<Iter>* buffer)`**
- Merges two sorted ranges using auxiliary buffer
- Optimized to copy smaller half to buffer

## Usage Example

```cpp
#include "TimSort/timsort.hpp"
#include <vector>

std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
Aads::TimSort(data.begin(), data.end());
// data is now sorted: {1, 2, 3, 4, 5, 6, 7, 8, 9}

// Works with any random access container
std::array<double, 5> arr = {3.14, 1.41, 2.71, 1.73, 0.57};
Aads::TimSort(arr.begin(), arr.end());
```

## Notes

- TimSort is the default sorting algorithm in Python and Java
- Particularly efficient for data with existing order or patterns
- Stable sort: maintains relative order of equal elements
- Adaptive: takes advantage of existing order in data
