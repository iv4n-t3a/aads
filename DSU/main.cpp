#include <cstddef>
#include <iostream>
#include <vector>

class DSU {
 public:
  DSU(size_t size) : ancestors_(size), rank_(size) {
    for (size_t i = 0; i < size; ++i) {
      ancestors_[i] = i;
    }
  }

  void Unite(size_t lhs, size_t rhs) {
    int lhs_anc = Find(lhs);
    int rhs_anc = Find(rhs);

    if (lhs_anc == rhs_anc) {
      return;
    }
    if (rank_[lhs_anc] < rank_[rhs_anc]) {
      std::swap(lhs_anc, rhs_anc);
    }
    rank_[lhs_anc] = std::max(rank_[lhs_anc], rank_[rhs_anc] + 1);
    ancestors_[rhs_anc] = lhs_anc;
  }

  bool AreSame(size_t lhs, size_t rhs) { return Find(lhs) == Find(rhs); }

 private:
  size_t Find(size_t idx) {
    if (ancestors_[idx] != idx) {
      ancestors_[idx] = Find(ancestors_[idx]);
    }
    return ancestors_[idx];
  }

  std::vector<size_t> ancestors_;
  std::vector<size_t> rank_;
};

int main() {
  int sets;
  int queryes;

  std::cin >> sets >> queryes;

  DSU dsu(sets);

  for (size_t i = 0; i < queryes; ++i) {
    char cmd;
    int lhs;
    int rhs;

    std::cin >> cmd >> lhs >> rhs;

    if (cmd == '+') {
      dsu.Unite(lhs - 1, rhs - 1);
    } else if (cmd == '?') {
      std::cout << dsu.AreSame(lhs - 1, rhs - 1) << std::endl;
    }
  }
}
