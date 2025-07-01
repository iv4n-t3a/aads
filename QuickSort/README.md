# QuickSort Implementation in C++

This file provides an implementation of the QuickSort algorithm. It is a generic implementation that supports custom comparators and random number generators, making it highly flexible and reusable.

## Features

- **Generic QuickSort**: Supports sorting any random-access container.
- **Custom Comparators**: Allows users to define their own comparison logic.
- **Custom Random Generators**: Enables the use of custom random number generators for pivot selection.
- **Modern C++ Concepts**: Utilizes C++20 concepts to enforce type constraints.

## Components

### Concepts

1. **RandomNumberGenerator**

  template <typename Rand>
  concept RandomNumberGenerator = requires(Rand rand) {
    { rand() } -> std::integral;
  };

Ensures that the random number generator provides integral values.

2. **Comparator**

  template <typename Comp, typename T>
  concept Comparator = requires(Comp comp, T lhs, T rhs) {
    { comp(lhs, rhs) } -> std::convertible_to<bool>;
  };

Ensures that the comparator can compare two elements and return a boolean-like result.

### Functions

**QuickSort**
The main QuickSort function.

  template <std::random_access_iterator Iter,
            Comparator<std::iter_value_t<Iter>> Comp = std::less<>,
            RandomNumberGenerator Rand = RandomGenerator>
  void QuickSort(Iter begin, Iter end, Comp comp = Comp(), Rand rand = Rand());

**Parameters**:
- `begin`, `end`: Iterators defining the range to sort.
- `comp`: Comparator for ordering elements (default: `std::less<>`).
- `rand`: Random number generator (default: `RandomGenerator`).

**Behavior**:
- Recursively partitions the range and sorts the subranges.

## Usage Example

#include "quicksort.hpp"
#include <vector>
#include <iostream>

int main() {
  std::vector<int> data = {3, 6, 8, 10, 1, 2, 1};
  Aads::QuickSort(data.begin(), data.end());
  for (int num : data) {
    std::cout << num << " ";
  }
}
```

## Notes

- The implementation assumes that the input range supports random access iterators.
- The default comparator (`std::less<>`) sorts elements in ascending order.
- The default random generator (`RandomGenerator`) uses a Mersenne Twister engine.
