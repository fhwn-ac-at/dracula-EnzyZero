#ifndef dice_h
#define dice_h

#include <algorithm>
#include <random>
#include <initializer_list> 
#include <time.h>

template<std::integral T, std::size_t F>
class dice {

public:  
  constexpr dice(size_t seed = time(nullptr), std::initializer_list<T>& list = {}) 
  : _gen( seed ), _d( _default_weights(list) )
  {
    static_assert(list.size() == F || list.size() == 0, "List must be equal to faces (F) of the dice or empty");
  }

  constexpr size_t operator()() { return _d(_gen) + 1; } // +1 as rolls start at 0

private: 
  std::mt19937 _gen;
  std::discrete_distribution<T> _d;

  constexpr auto _default_weights(std::initializer_list<T> list) -> std::initializer_list<T>
  {
    // fill with equal weights if no weights supplied
    if ( std::ranges::all_of(list, [](T e) { return e == 0; }) )
    {
      std::ranges::fill(list, 1);
      return list;
    } 

    return list; 
  }

};
  
#endif
