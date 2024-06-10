#include <array>
#include <iostream>
#include <cstdint>
#include <vector>

namespace Consts {
constexpr size_t kBitsPerByte = 8;
constexpr size_t kBytesCount = 1 << kBitsPerByte;
constexpr size_t kMaxByte = kBytesCount - 1;
constexpr size_t kBitsPerInt = 64;
constexpr size_t kBytesPerInt = kBitsPerInt / kBitsPerByte;
}  // namespace Consts

int GetByte(uint64_t num, size_t byte_num) {
  return (num >> (byte_num * Consts::kBitsPerByte)) & Consts::kMaxByte;
}

class Counter {
 public:
  Counter(const std::vector<uint64_t>& nums, size_t byte_num) {
    for (size_t i = 0; i < Consts::kBytesCount; ++i) {
      count_[i] = 0;
      used_[i] = 0;
    }
    for (uint64_t num : nums) {
      count_[GetByte(num, byte_num)] += 1;
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

void SortByByte(std::vector<uint64_t>& nums, size_t byte_num) {
  Counter counter(nums, byte_num);
  std::vector<uint64_t> copy(nums.size());
  for (size_t i = 0; i < nums.size(); ++i) {
    int byte_value = GetByte(nums[i], byte_num);
    copy[counter.PutIndex(byte_value)] = nums[i];
    counter.IncrementUsed(byte_value);
  }
  nums.swap(copy);
}

void LSDSort(std::vector<uint64_t>& nums) {
  for (size_t i = 0; i < Consts::kBytesPerInt; ++i) {
    SortByByte(nums, i);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t len;
  std::cin >> len;

  std::vector<uint64_t> nums(len);

  for (uint64_t& num : nums) {
    std::cin >> num;
  }

  LSDSort(nums);

  for (uint64_t num : nums) {
    std::cout << num << "\n";
  }
}
