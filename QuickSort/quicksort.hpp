#include <concepts>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <random>

namespace Aads {

namespace {

template <typename Comp, typename Iter>
concept Comparator =
    std::relation<Comp, std::iter_value_t<Iter>, std::iter_value_t<Iter>>;

template <std::random_access_iterator Iter, Comparator<Iter> Comp = std::less<>>
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

template <std::random_access_iterator Iter>
Iter PickPivot(Iter begin, Iter end) {
  static auto rnd = std::mt19937(std::random_device()());
  size_t idx = rnd() % (end - begin);
  return begin + idx;
}

}  // namespace

template <std::random_access_iterator Iter, Comparator<Iter> Comp = std::less<>>
void QuickSort(Iter begin, Iter end, Comp comp = Comp()) {
  if (begin == end or begin >= end - 1) {
    return;
  }
  Iter pivot = PickPivot(begin, end);
  Iter mid = Partition(begin, end, pivot, comp);
  QuickSort(begin, mid, comp);
  QuickSort(mid, end, comp);
}

}  // namespace Aads
