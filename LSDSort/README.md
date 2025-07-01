### LSD Sort(Radix sort)

The `LSDSort` method implements the Least Significant Digit (LSD) radix sort algorithm for sorting 64-bit unsigned integers. It operates with **O(n)** time complexity, making it highly efficient for large datasets.

## Template Parameters
- `Iter`: A random-access iterator pointing to the range of elements to be sorted. The value type of the iterator must be `uint64_t`.
- `ResIter`: A random-access iterator pointing to the range where the sorted elements will be stored. The value type of the iterator must also be `uint64_t`.

## Parameters
- `begin`: The beginning of the range to be sorted.
- `end`: The end of the range to be sorted.
- `result_begin`: The beginning of the range where the sorted elements will be stored.
- `result_end`: The end of the range where the sorted elements will be stored.

## Requirements
1. The input range `[begin, end)` and the output range `[result_begin, result_end)` must not overlap. This is because the algorithm alternates between two buffers during the sorting process.
2. The size of the output range `[result_begin, result_end)` must be equal to the size of the input range `[begin, end)`.

## Key Features
- The algorithm processes the integers byte by byte, starting from the least significant byte.
- It alternates between the input and output buffers for each byte processed.
- The method ensures stable sorting for each byte.

## Example Usage
```cpp
#include <vector>
#include "LSDSort/lsd_sort.hpp"

int main() {
  std::vector<uint64_t> data = {123, 456, 20, 23};
  std::vector<uint64_t> result(data.size());
  Aads::LSDSort(data.begin(), data.end(), result.begin(), result.end());
}
```
