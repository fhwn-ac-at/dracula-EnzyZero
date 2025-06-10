#ifndef dice_h
#define dice_h

#include <array>
#include <algorithm>

namespace dice {

template<std::integral T, std::size_t F>
using weights_list_t = std::array<T, F>; 

template <std::integral T, size_t F>
consteval auto weight_generator(weights_list_t<T, F> list) -> std::array<T, F>
{
  std::array<T, F> ret_arr{};

  bool is_empty = std::all_of(list.begin(), list.end(), [](T e) { return e == 0; });
  
  // fill with equal weights if no weights supplied
  if (is_empty)
  {
    std::fill(ret_arr.begin(), ret_arr.end(), 1);
    return ret_arr;
  } 

  // else use given weights
  std::copy(list.begin(), list.end(), ret_arr.begin());
  return ret_arr;
}

} // dice namespace 
  
#endif
