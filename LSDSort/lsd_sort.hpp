#include <array>
#include <cstdint>
#include <iterator>
#include <vector>

namespace Aads {

template <typename Iter>
concept uint64_random_access_iterator =
    std::is_same_v<typename std::iterator_traits<Iter>::value_type, uint64_t> &&
    std::random_access_iterator<Iter>;

namespace {

namespace Consts {
constexpr size_t kBitsPerByte = 8;
constexpr size_t kBitsPerByteLog = 3;
constexpr size_t kBytesCount = 1 << kBitsPerByte;
constexpr size_t kMaxByte = kBytesCount - 1;
constexpr size_t kBitsPerInt = 64;
constexpr size_t kBytesPerInt = kBitsPerInt / kBitsPerByte;
}  // namespace Consts

int GetByte(uint64_t num, size_t byte_num) {
  return (num >> (byte_num << Consts::kBitsPerByteLog)) & Consts::kMaxByte;
}

class Counter {
 public:
  template <uint64_random_access_iterator Iter>
  void Initialize(Iter begin, Iter end, size_t byte_num) {
    for (size_t i = 0; i < Consts::kBytesCount; ++i) {
      count_[i] = 0;
      used_[i] = 0;
    }
    for (Iter i = begin; i != end; ++i) {
      count_[GetByte(*i, byte_num)] += 1;
    }
    prefsum_[0] = 0;
    for (size_t i = 1; i < Consts::kBytesCount; ++i) {
      prefsum_[i] = prefsum_[i - 1] + count_[i - 1];
    }
  }

  size_t PutIndex(int byte_value) {
    return prefsum_[byte_value] + used_[byte_value];
  }

  void IncrementUsed(int byte_value) { used_[byte_value] += 1; }

 private:
  std::array<size_t, Consts::kBytesCount> count_;
  std::array<size_t, Consts::kBytesCount> prefsum_;
  std::array<size_t, Consts::kBytesCount> used_;
};

template <uint64_random_access_iterator Iter,
          uint64_random_access_iterator ResIter>
void SortByByte(Iter begin, Iter end, ResIter res, size_t byte_num) {
  thread_local static Counter counter;
  counter.Initialize(begin, end, byte_num);

  for (Iter i = begin; i != end; ++i) {
    int byte_value = GetByte(*i, byte_num);
    *(res + counter.PutIndex(byte_value)) = *i;
    counter.IncrementUsed(byte_value);
  }
}

}  // namespace

template <uint64_random_access_iterator Iter,
          uint64_random_access_iterator ResIter>
void LSDSort(Iter begin, Iter end, ResIter result_begin, ResIter result_end) {
  if (begin == end) {
    return;
  }
  assert(result_end - result_begin == end - begin);
  static_assert(Consts::kBytesPerInt % 2 == 0);
  for (size_t i = 0; i < Consts::kBytesPerInt; i += 2) {
    SortByByte(begin, end, result_begin, i);
    SortByByte(result_begin, result_end, begin, i + 1);
  }
}

}  // namespace Aads
