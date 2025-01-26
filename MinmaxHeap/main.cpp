#include <bit>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

uint32_t Log2(uint32_t num) {
  num |= num >> (1 << 4);
  num |= num >> (1 << 3);
  num |= num >> (1 << 2);
  num |= num >> (1 << 1);
  num |= num >> 1;
  return std::popcount(num);
}

/* http://www.akira.ruc.dk/~keld/teaching/algoritmedesign_f03/Artikler/02/Atkinson86.pdf
 */
template <typename T>
class MinMaxHeap {
 public:
  MinMaxHeap() { heap_.push_back(0); }

  T& GetMin() { return heap_[0]; }
  T& GetMax() { return heap_[MaxChild(0)]; }
  const T& GetMin() const { return heap_[0]; }
  const T& GetMax() const { return heap_[MaxChild(0)]; }

  size_t Size() const { return heap_.size() - 1; }

  void Clear() {
    heap_.clear();
    heap_.push_back(0);
  }

  void Insert(const T& new_elem) {
    heap_.push_back(new_elem);
    SiftUp(heap_.size() - 1);
  }

  void Insert(T&& new_elem) {
    heap_.push_back(new_elem);
    SiftUp(heap_.size() - 1);
  }

  template <typename... Args>
  void Emplace(Args&&... args) {
    heap_.emplace_back(std::forward<Args>(args)...);
    SiftUp(heap_.size() - 1);
  }

  void ExtractMin() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(0);
  }

  void ExtractMax() {
    size_t to_swap = MaxChild(0);
    std::swap(heap_[to_swap], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(to_swap);
  }

  void Print() {
    for (size_t i = 0; i < Log2(heap_.size()); ++i) {
      for (size_t j = 1 << i; j < 1ULL << (i + 1); ++j) {
        if (j >= heap_.size()) {
          break;
        }
        std::cout << heap_[j - 1] << ' ';
      }
      std::cout << std::endl;
    }
  }

 private:
  void SiftUp(size_t idx) {
    if (IsOnMinLevel(idx)) {
      if (heap_[idx] > heap_[GetParent(idx)]) {
        std::swap(heap_[idx], heap_[GetParent(idx)]);
        SiftUpMax(GetParent(idx));
      } else {
        SiftUpMin(idx);
      }
    } else {
      if (heap_[idx] < heap_[GetParent(idx)]) {
        std::swap(heap_[idx], heap_[GetParent(idx)]);
        SiftUpMin(GetParent(idx));
      } else {
        SiftUpMax(idx);
      }
    }
  }

  void SiftUpMax(size_t idx) {
    while (heap_[GetGrParent(idx)] < heap_[idx]) {
      std::swap(heap_[GetGrParent(idx)], heap_[idx]);
      idx = GetGrParent(idx);
    }
  }

  void SiftUpMin(size_t idx) {
    while (heap_[GetGrParent(idx)] > heap_[idx]) {
      std::swap(heap_[GetGrParent(idx)], heap_[idx]);
      idx = GetGrParent(idx);
    }
  }
  void SiftDown(size_t idx) {
    if (IsOnMinLevel(idx)) {
      SiftDownMin(idx);
    } else {
      SiftDownMax(idx);
    }
  }

  void SiftDownMin(size_t idx) {
    size_t minchd = MinChildOrGrChild(idx);

    if (heap_[minchd] >= heap_[idx]) {
      return;
    }

    if (GetGrParent(minchd) == idx) {
      std::swap(heap_[idx], heap_[minchd]);
      if (heap_[minchd] > heap_[GetParent(minchd)]) {
        std::swap(heap_[minchd], heap_[GetParent(minchd)]);
      }
      SiftDown(minchd);
    } else {
      std::swap(heap_[minchd], heap_[idx]);
    }
  }
  void SiftDownMax(size_t idx) {
    size_t maxchd = MaxChildOrGrChild(idx);

    if (heap_[maxchd] <= heap_[idx]) {
      return;
    }

    if (GetGrParent(maxchd) == idx) {
      std::swap(heap_[idx], heap_[maxchd]);
      if (heap_[maxchd] < heap_[GetParent(maxchd)]) {
        std::swap(heap_[maxchd], heap_[GetParent(maxchd)]);
      }
      SiftDown(maxchd);
    } else {
      std::swap(heap_[maxchd], heap_[idx]);
    }
  }

  size_t LastListInSubtree(size_t idx) {
    while (GetLeftChild(idx) != idx) {
      idx = GetParent(idx);
    }
    return idx;
  }

  size_t MaxChildOrGrChild(size_t idx) {
    size_t max_child = MaxChild(idx);
    size_t max_grchild = MaxGrChild(idx);
    return MaxIdx(max_child, max_grchild);
  }
  size_t MinChildOrGrChild(size_t idx) {
    size_t min_child = MinChild(idx);
    size_t min_grchild = MinGrChild(idx);
    return MinIdx(min_child, min_grchild);
  }

  size_t MinGrChild(size_t idx) {
    size_t min_grchild_left = MinChild(GetLeftChild(idx));
    size_t min_grchild_right = MinChild(GetRightChild(idx));
    return MinIdx(min_grchild_left, min_grchild_right);
  }
  size_t MaxGrChild(size_t idx) {
    size_t max_grchild_left = MaxChild(GetLeftChild(idx));
    size_t max_grchild_right = MaxChild(GetRightChild(idx));
    return MaxIdx(max_grchild_left, max_grchild_right);
  }

  size_t MinChild(size_t idx) {
    return MinIdx(GetLeftChild(idx), GetRightChild(idx));
  }
  size_t MaxChild(size_t idx) {
    return MaxIdx(GetLeftChild(idx), GetRightChild(idx));
  }

  size_t MinIdx(size_t idx1, size_t idx2) {
    if (heap_[idx1] < heap_[idx2]) {
      return idx1;
    }
    return idx2;
  }
  size_t MaxIdx(size_t idx1, size_t idx2) {
    if (heap_[idx1] > heap_[idx2]) {
      return idx1;
    }
    return idx2;
  }

  static bool IsOnMinLevel(size_t idx) { return Log2(idx) % 2 == 0; }
  static size_t GetParent(size_t idx) { return idx == 0 ? 0 : (idx - 1) / 2; }

  static size_t GetGrParent(size_t idx) {
    return idx < 4 ? idx : GetParent(GetParent(idx));
  }

  size_t GetLeftChild(size_t idx) {
    return 2 * idx + 1 < heap_.size() ? 2 * idx + 1 : idx;
  }
  size_t GetRightChild(size_t idx) {
    return 2 * idx + 2 < heap_.size() ? 2 * idx + 2 : idx;
  }

  std::vector<T> heap_;
};

void ProcessCMD(MinMaxHeap<int64_t>& heap, std::string cmd) {
  if (cmd == "insert") {
    int64_t val;
    std::cin >> val;
    heap.Insert(val);
    std::cout << "ok\n";
  } else if (cmd == "get_min") {
    if (heap.Size() == 0) {
      std::cout << "error\n";
    } else {
      std::cout << heap.GetMin() << "\n";
    }
  } else if (cmd == "get_max") {
    if (heap.Size() == 0) {
      std::cout << "error\n";
    } else {
      std::cout << heap.GetMax() << "\n";
    }
  } else if (cmd == "size") {
    std::cout << heap.Size() << "\n";
  } else if (cmd == "clear") {
    heap.Clear();
    std::cout << "ok\n";
  } else if (cmd == "extract_min") {
    if (heap.Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << heap.GetMin() << "\n";
    heap.ExtractMin();
  } else if (cmd == "extract_max") {
    if (heap.Size() == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << heap.GetMax() << "\n";
    heap.ExtractMax();
  } else if (cmd == "print") {
    heap.Print();
  }
}

int main() {
  MinMaxHeap<int64_t> heap;

  std::string cmd;
  size_t query_count;

  std::cin >> query_count;

  for (size_t i = 0; i < query_count; ++i) {
    std::cin >> cmd;
    ProcessCMD(heap, cmd);
  }
}
