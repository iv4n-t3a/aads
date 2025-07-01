#include <concepts>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <random>
#include <utility>

namespace Aads {

namespace {

template <typename Rand>
concept RandomNumberGenerator = requires(Rand rand) {
  { rand() } -> std::integral;
};

template <typename Comp, typename T>
concept Comparator = requires(Comp comp, T lhs, T rhs) {
  { comp(lhs, rhs) } -> std::convertible_to<bool>;
};

class RandomGenerator {
 public:
  RandomGenerator() {
    std::random_device rd;
    rand_ = std::mt19937(rd());
  }

  size_t operator()() { return rand_(); }

 private:
  std::mt19937 rand_;
};

template <std::random_access_iterator Iter,
          Comparator<std::iter_value_t<Iter>> Comp = std::less<>>
Iter Partition(Iter begin, Iter end, Iter pivot, Comp comp) {
  std::swap(*pivot, *(end - 1));  // Move pivot to the end
  Iter mid = begin;
  for (Iter it = begin; it < end - 1; ++it) {
    if (comp(*it, *(end - 1))) {
      std::swap(*it, *mid);
      ++mid;
    }
  }
  std::swap(*(end - 1), *mid);  // Move pivot to its final place
  return mid;

  while (true) {
    while (comp(*begin, *pivot)) {
      ++begin;
    }
    while (comp(*pivot, *(end - 1))) {
      --end;
    }
    if (begin >= end - 1) {
      return end;
    }
    std::swap(*begin, *(end - 1));
    ++begin;
    --end;
  }
}

template <std::random_access_iterator Iter, RandomNumberGenerator Rand>
Iter PickPivot(Iter begin, Iter end, Rand& rand) {
  size_t idx = rand() % (end - begin);
  return begin + idx;
}

}  // namespace

template <std::random_access_iterator Iter,
          Comparator<std::iter_value_t<Iter>> Comp = std::less<>,
          RandomNumberGenerator Rand = RandomGenerator>
void QuickSort(Iter begin, Iter end, Comp comp = Comp(), Rand rand = Rand()) {
  if (begin == end or begin >= end - 1) {
    return;
  }
  Iter pivot = PickPivot(begin, end, rand);
  Iter mid = Partition(begin, end, pivot, comp);
  QuickSort(begin, mid, comp);
  QuickSort(mid, end, comp);
}

}  // namespace Aads
