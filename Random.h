#pragma once

#include <random>
#include <type_traits>

static std::random_device rd;
static std::mt19937 mt(rd());

namespace Random
{
  template <typename T>
  static T get(T low, T high)
  {
    static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type");

    if (low <= high)
    {
      std::uniform_int_distribution<T> dist(low, high);
      return dist(mt);
    }
    else
    {
      std::uniform_int_distribution<T> dist(high, low);
      return dist(mt);
    }
  }
}