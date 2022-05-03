#pragma once

#include <random>

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_int_distribution<int16_t> dist(-10000, 10000);

namespace Random
{
  static int16_t get()
  {
    return dist(mt);
  }
}