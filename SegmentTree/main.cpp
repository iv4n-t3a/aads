#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template <typename T>
class SegmentTree {
 public:
  template <typename Iter>
  SegmentTree(Iter begin, Iter end,
              std::function<const T&(const T&, const T&)> func)
      : size_(std::distance(begin, end)), tree_(size_ * 2), func_(func) {
    std::copy(begin, end, tree_.begin() + size_);

    for (size_t i = size_ - 1; i > 0; i--) {
      tree_[i] = func_(tree_[2 * i], tree_[2 * i + 1]);
    }
  }

  int Calc(int left, int right) {
    left += size_;
    right += size_;
    T res = tree_[right--];

    while (left <= right) {
      if (left % 2 == 1) {
        res = func_(tree_[left], res);
        left += 1;
      }
      if (right % 2 == 0) {
        res = func_(tree_[right], res);
        right -= 1;
      }
      left /= 2;
      right /= 2;
    }
    return res;
  }

  void Set(size_t idx, T value) {
    idx += size_;
    tree_[idx] = value;
    for (size_t i = idx / 2; i > 0; i /= 2) {
      tree_[i] = func_(tree_[2 * i], tree_[2 * i + 1]);
    }
  }

  size_t Size() { return size_; }

 private:
  size_t size_;
  std::vector<T> tree_;
  std::function<const T&(const T&, const T&)> func_;
};

std::vector<int> InputArray(std::istream& inp) {
  size_t elements;
  inp >> elements;

  std::vector<int> data(elements);

  for (size_t i = 0; i < elements; ++i) {
    inp >> data[i];
  }

  return data;
}

void ProcessQueryes(std::istream& inp, std::ostream& outp,
                    const std::vector<int>& data) {
  SegmentTree<int> tree(data.begin(), data.end(),
                        (const int& (*)(const int&, const int&))std::min<int>);

  size_t queryies;
  inp >> queryies;

  for (size_t i = 0; i < queryies; ++i) {
    char command;
    inp >> command;

    if (command == '?') {
      int left;
      int right;
      inp >> left >> right;
      outp << tree.Calc(left, right) << "\n";
    } else if (command == '=') {
      int index;
      int value;
      inp >> index >> value;
      tree.Set(index, value);
    }
  }
}

int main() {
  std::vector<int> data = InputArray(std::cin);
  ProcessQueryes(std::cin, std::cout, data);
}
