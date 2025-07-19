#include <vector>

namespace Aads {

// TODO: Add custom comparator support
// TODO: Override move-constructor and move-assign operator
template <typename T>
class Heap {
 public:
  T& GetMax() { return heap_[0]; }
  const T& GetMax() const { return heap_[0]; }

  void Reserve(size_t size) { heap_.reserve(size); }

  size_t Size() const { return heap_.size(); }

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

  void ExtractMax() {
    std::swap(heap_[0], heap_[heap_.size() - 1]);
    heap_.pop_back();
    SiftDown(0);
  }

 private:
  void SiftUp(size_t idx) {
    while (heap_[GetParent(idx)] < heap_[idx]) {
      std::swap(heap_[GetParent(idx)], heap_[idx]);
      idx = GetParent(idx);
    }
  }

  void SiftDown(size_t idx) {
    while (true) {
      size_t min_child = GetLeftChild(idx);
      size_t max_child = GetRightChild(idx);
      if (heap_[min_child] > heap_[max_child]) {
        std::swap(min_child, max_child);
      }

      if (heap_[max_child] > heap_[idx]) {
        std::swap(heap_[idx], heap_[max_child]);
        idx = max_child;
      } else if (heap_[min_child] > heap_[idx]) {
        std::swap(heap_[idx], heap_[min_child]);
        idx = min_child;
      } else {
        break;
      }
    }
  }

  static size_t GetParent(size_t idx) { return idx == 0 ? 0 : (idx - 1) / 2; }

  size_t GetLeftChild(size_t idx) {
    return 2 * idx + 1 < heap_.size() ? 2 * idx + 1 : idx;
  }

  size_t GetRightChild(size_t idx) {
    return 2 * idx + 2 < heap_.size() ? 2 * idx + 2 : idx;
  }

  std::vector<T> heap_;
};

}  // namespace Aads
