#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

size_t Partition(std::vector<int>& array, size_t left, size_t right,
                 int pivot) {
  while (true) {
    while (array[left] < pivot) {
      left += 1;
    }
    while (array[right] > pivot) {
      right -= 1;
    }
    if (left >= right) {
      return right;
    }
    std::swap(array[left], array[right]);
    left += 1;
    right -= 1;
  }
}

int PickPivot(std::vector<int> const& array, size_t left, size_t right) {
  size_t idx = left + std::rand() % (right - left + 1);
  return array[idx];
}

void QuickSort(std::vector<int>& array, size_t left, size_t right) {
  if (left >= right) {
    return;
  }
  int pivot = PickPivot(array, left, right);
  size_t mid = Partition(array, left, right, pivot);
  QuickSort(array, left, mid);
  QuickSort(array, mid + 1, right);
}

int main() {
  std::srand(std::time(nullptr));
  size_t len;
  std::cin >> len;
  std::vector<int> array(len);

  for (int& num : array) {
    std::cin >> num;
  }

  QuickSort(array, 0, array.size() - 1);

  for (int num : array) {
    std::cout << num << std::endl;
  }
}
