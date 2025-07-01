#include <concepts>

#pragma once

namespace Aads {

namespace Util {

template <typename Rand>
concept RandomNumberGenerator = requires(Rand rand) {
  { rand() } -> std::integral;
};

template <typename Comp, typename T>
concept Comparator = requires(Comp comp, T lhs, T rhs) {
  { comp(lhs, rhs) } -> std::convertible_to<bool>;
};

}  // namespace Util

}  // namespace Aads
