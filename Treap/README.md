# Treap Class Documentation

The `Treap` class is a data structure that combines the properties of a binary search tree and a heap. It supports efficient insertion, deletion, and access operations while maintaining a balanced structure relying on randomized priorities given to each node.

## Template Parameters
- `T`: The type of elements stored in the Treap.
- `Comp`: A comparator type (default: `std::less<>`), must satisfy `std::relation<T, T>`

## Constructors
- **`Treap()`**: Default constructor that initializes an empty Treap.
- **`Treap(std::initializer_list<T> init_list)`**: Constructs a Treap from an initializer list of elements.
- **`Treap(const Treap& treap)`**: Copy constructor.
- **`Treap(Treap&& treap)`**: Move constructor.

## Operators
- **`Treap& operator=(const Treap& other)`**: Copy assignment operator.
- **`Treap& operator=(Treap&& other)`**: Move assignment operator.
- **`T& operator[](size_t index)`**: Accesses the element at the specified index.

## Methods
- **`void Insert(size_t index, const T& value)`**: Inserts a value at the specified index.
- **`void Insert(size_t index, T&& value)`**: Inserts a value (rvalue) at the specified index.
- **`T& Min(size_t left, size_t right)`**: Returns the minimum value in the range `[left, right)`.
- **`void Reverse(size_t left, size_t right)`**: Reverses the elements in the range `[left, right)`.
- **`void Reverse()`**: Reverses order of elements in entire struct.
- **`static Treap Merge(Treap&& left, Treap&& right)`**: Merges two Treaps into one.
- **`std::pair<Treap, Treap> Split(size_t del) &&`**: Splits the Treap into two at the specified index.
- **`size_t Size() const`**: Returns the number of elements in the Treap.
- **`void Print(std::ostream& out = std::cout)`**: Prints the Treap structure to the specified output stream.

## Time complexity

- **`Treap(const Treap&)`** - O(N)
- **`Treap(Treap&&)`** - O(1)
- **`Insert`** - O(log N)
- **`Min`** - O(log N)
- **`Reverse(l, r)`** - O(log N)
- **`Reverse`** - O(1)
- **`Merge`** - O(log N)
- **`Split`** - O(log N)
- **`operator[]`** - O(log N)

## Example Usage
```cpp
#include "Treap/treap.hpp"
#include <iostream>

int main() {
    Aads::Treap<int> treap = {1, 2, 3, 4, 5};
    treap.Insert(2, 10);
    std::cout << "Element at index 2: " << treap[2] << std::endl;
    treap.Reverse(1, 4);
    treap.Print();
    return 0;
}
```
