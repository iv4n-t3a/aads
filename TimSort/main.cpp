#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

template <std::input_iterator Iter>
using ValType = typename std::iterator_traits<Iter>::value_type;

// https://habr.com/ru/companies/infopulse/articles/133303/
size_t CalcMinRun(size_t size) {
  const size_t kLower = 64;
  size_t res = 0;
  while (size >= kLower) {
    res |= size & 1;
    size >>= 1;
  }
  return size + res;
}

template <std::random_access_iterator Iter>
void InsertionSort(Iter begin, Iter end) {
  for (int i = 1; i < end - begin; ++i) {
    if (*(begin + i - 1) < *(begin + i)) {
      continue;
    }

    int to_insert = 0;
    for (; to_insert < i; ++to_insert) {
      if (*(begin + i) < *(begin + to_insert)) {
        break;
      }
    }

    auto elem = std::move(*(begin + i));

    for (int j = i; j > to_insert; --j) {
      *(begin + j) = *(begin + j - 1);
    }

    *(begin + to_insert) = std::move(elem);
  }
}

template <std::random_access_iterator Iter>
void Merge(Iter begin, Iter mid, Iter end, ValType<Iter>* buffer) {
  size_t res_size = end - begin;
  size_t size1 = mid - begin;
  size_t size2 = end - mid;

  if (size1 < size2) {
    std::copy(begin, mid, buffer);
    size_t index1 = 0;
    size_t index2 = 0;

    for (size_t i = 0; i < res_size; ++i) {
      if (index2 == size2 or
          (index1 != size1 and *(buffer + index1) < *(mid + index2))) {
        *(begin + i) = *(buffer + index1);
        ++index1;
      } else {
        *(begin + i) = *(mid + index2);
        ++index2;
      }
    }
  } else {
    std::copy(mid, end, buffer);
    ssize_t index1 = size1 - 1;
    ssize_t index2 = size2 - 1;

    for (ssize_t i = res_size - 1; i >= 0; --i) {
      if (index2 == -1 or
          (index1 != -1 and *(buffer + index2) < *(begin + index1))) {
        *(begin + i) = *(begin + index1);
        --index1;
      } else {
        *(begin + i) = *(buffer + index2);
        --index2;
      }
    }
  }
}

template <std::random_access_iterator Iter>
struct Run {
  Iter begin;
  Iter end;

  size_t Size() { return end - begin; }
};

template <std::random_access_iterator Iter>
void RebalanceStack(std::vector<Run<Iter>>& runs, ValType<Iter>* buff) {
  while (runs.size() >= 3) {
    Run xrun = *(runs.end() - 3);
    Run yrun = *(runs.end() - 2);
    Run zrun = *(runs.end() - 1);

    if (xrun.Size() > yrun.Size() + zrun.Size() and yrun.Size() > zrun.Size()) {
      return;
    }

    if (xrun.Size() < zrun.Size()) {
      Merge(xrun.begin, xrun.end, yrun.end, buff);
      runs.pop_back();
      *(runs.end() - 2) = {xrun.begin, yrun.end};
      *(runs.end() - 1) = zrun;
    } else {
      Merge(yrun.begin, yrun.end, zrun.end, buff);
      runs.pop_back();
      *(runs.end() - 2) = xrun;
      *(runs.end() - 1) = {yrun.begin, zrun.end};
    }
  }
}

template <std::random_access_iterator Iter>
std::vector<Run<Iter>> PrepareRuns(Iter begin, Iter end, ValType<Iter>* buff,
                                   size_t minrun) {
  std::vector<Run<Iter>> runs;
  Iter iter = begin;

  do {
    if (not runs.empty() and *(runs.back().end - 1) < *iter) {
      ++iter;
      runs.back().end = iter;
    } else {
      RebalanceStack(runs, buff);

      runs.push_back({iter, iter + minrun});

      if (static_cast<size_t>(end - runs.back().end) < minrun) {
        runs.back().end = end;
      }

      iter = runs.back().end;
      InsertionSort(runs.back().begin, runs.back().end);
    }
  } while (runs.back().end != end);
  RebalanceStack(runs, buff);

  return runs;
}

template <std::random_access_iterator Iter>
void TimSort(Iter begin, Iter end) {
  ValType<Iter>* buff = reinterpret_cast<ValType<Iter>*>(
      new std::byte[sizeof(ValType<Iter>) * (end - begin) / 2]);

  size_t minrun = CalcMinRun(end - begin);
  std::vector<Run<Iter>> runs = PrepareRuns(begin, end, buff, minrun);

  while (runs.size() != 1) {
    Iter runbegin = (runs.end() - 2)->begin;
    Iter runmid = (runs.end() - 2)->end;
    Iter runend = (runs.end() - 1)->end;

    Merge(runbegin, runmid, runend, buff);
    runs.pop_back();
    *(runs.end() - 1) = {runbegin, runend};
  }

  delete[] reinterpret_cast<std::byte*>(buff);
}

std::vector<int> InputVector(std::istream& inp) {
  size_t size;
  inp >> size;

  std::vector<int> vector(size);

  for (int& elem : vector) {
    inp >> elem;
  }

  return vector;
}

template <std::forward_iterator Iter>
void PrintRange(std::ostream& outp, Iter begin, Iter end) {
  for (; begin != end; ++begin) {
    outp << *begin << ' ';
  }
  outp << std::endl;
}

int main() {
  std::vector<int> arr = InputVector(std::cin);
  TimSort(arr.begin(), arr.end());
  PrintRange(std::cout, arr.begin(), arr.end());
}
