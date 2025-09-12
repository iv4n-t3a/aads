#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <vector>

#pragma once

// Consider using lightweight type T as it will be
// copyed a lot
template <typename T, std::predicate<T, T> F>
class SegmentTree {
 public:
  template <std::input_iterator Iter>
  SegmentTree(Iter begin, Iter end, F func = F{})
      : size_(std::distance(begin, end)), tree_(size_ * 2), func_(func) {
    std::copy(begin, end, tree_.begin() + size_);

    for (size_t i = size_ - 1; i > 0; i--) {
      tree_[i] = func_(tree_[2 * i], tree_[(2 * i) + 1]);
    }
  }

  SegmentTree(std::initializer_list<T> list, F func = F{})
      : SegmentTree(list.begin(), list.end(), func) {}

  SegmentTree(const SegmentTree& other)
      : size_(other.size_), tree_(other.tree_), func_(other.func_) {}

  T Calc(size_t begin, size_t end) const {
    begin += size_;
    end += size_;
    T res = tree_[begin++];

    while (begin < end) {
      if (begin % 2 == 1) {
        res = func_(tree_[begin], res);
        begin += 1;
      }
      if (end % 2 == 1) {
        res = func_(tree_[end - 1], res);
        end -= 1;
      }
      begin /= 2;
      end = (end - 1) / 2 + 1;
    }
    return res;
  }

  void Set(size_t idx, const T& value) {
    idx += size_;
    tree_[idx] = value;
    for (size_t i = idx / 2; i > 0; i /= 2) {
      tree_[i] = func_(tree_[2 * i], tree_[(2 * i) + 1]);
    }
  }

  const T& operator[](size_t index) const { return tree_[index + size_]; }
  size_t Size() const { return size_; }

 private:
  size_t size_;
  std::vector<T> tree_;
  F func_;
};
