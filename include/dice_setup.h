#ifndef dice_setup_h
#define dice_setup_h

#include <array>
#include <algorithm>
#include <common.h> 
namespace dice {

template <std::integral T, size_t F>
consteval std::array<T, F> weight_generator(cmn::dice_weights_list_t<T, F> list)
{
  std::array<T, F> ret_arr{};

  bool is_empty = std::none_of(list.begin(), list.end(), [](T e) { return !!e; });
  
  // fill with equal weights if no weights supplied
  if (is_empty)
  {
    std::fill(ret_arr.begin(), ret_arr.end(), 1);
    return ret_arr;
  } 

  // use given weights
  std::copy(list.begin(), list.end(), ret_arr.begin());
  return ret_arr;
}

} // dice namespace 
  
#endif
