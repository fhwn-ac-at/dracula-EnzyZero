#ifndef dice_h
#define dice_h

#include <assert.h>
#include <algorithm>
#include <random>
#include <ranges> 
#include <time.h>

template<std::integral T, std::size_t F>
class Dice {

public:

  template <std::ranges::input_range R>
  requires std::same_as<double, std::ranges::range_value_t<R>>
  constexpr Dice(R&& weights, size_t seed = time(nullptr))
  : _gen( seed )
  {
    assert(std::ranges::size(weights) == F || std::ranges::empty(weights) );
 
    // assign the weights if not empty 
    if ( std::ranges::any_of(weights, [](T e) { return e != 0; }) )
    {
      _d = { weights.begin(), weights.end() };
      return;
    }

    // else fill with ones
    std::array<double, F> arr;
    arr.fill(1);
    _d = { arr.begin(), arr.end() };
 }

  size_t operator()() { return _d(_gen) + 1; } // +1 as rolls start at 0
  auto roll() { return operator()(); }

private: 
  std::mt19937 _gen;
  std::discrete_distribution<T> _d;
};
  
#endif
