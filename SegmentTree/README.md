# Segment Tree Documentation

Segment Tree supports efficient function calculation on range

## Template Parameters
- `T`: The type of elements stored in the SegmentTree. **Consider usinglight trivialy copyed data type** as it's not going to be copyed a lot.
- `Comp`: A function type, must satisfy `std::predicate<T, T>`. For correct work **function is required to guarante `f(f(a, b), c) = f(a, f(b, c))`**

## Constructors
- **`SegmentTree(Iter begin, Iter end, F func = F{})`**: Constructs SegmentTree from pair of iterators and function.
- **`SegmentTree(std::initializer_list<T> init_list, F func = F{})`**: Constructs a SegmentTree from an initializer list of elements and function.
- **`SegmentTree(const SegmentTree&)`**: Copy constructor.

## Operators
- **`const T& operator[](size_t index)`**: Accesses the element at the specified index.

## Methods
- **`void Set(size_t index, const T& value)`**: Updates a value at the specified index.
- **`void Calc(size_t begin, size_t end) const`**: Calculates F value on `[begin, end)` range
- **`void Size() const`**: Obtains count of elements.

## Time complexity

- **`SegmentTree(Iter, Iter)`** - O(N)
- **`SegmentTree(const SegmentTree&)`** - O(N)
- **`Set`** - O(log N)
- **`Calc`** - O(log N)

## Example Usage
```cpp
#include "SegmentTree/segment_tree.hpp"
#include <iostream>
#include <cassert>

int main() {
  std::vector<int> data = {5, 2, 6, 3, 7, 1, 4};
  SegmentTree<int, Func> seg_tree(data.begin(), data.end(), min_func);

  seg_tree.Set(3, 0);
  assert(seg_tree.Calc(0, 7) == 0);
  assert(seg_tree.Calc(3, 6) == 0);
}
```
