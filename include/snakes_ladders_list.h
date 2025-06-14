#ifndef snakes_ladders_list_h 
#define snakes_ladders_list_h  

#include <assert.h>
#include <initializer_list>
#include <concepts>
#include <algorithm>
#include <ranges>
#include <array>
#include <utility> 

#include "vec.h"

namespace snakes_and_ladders {   
  
template <std::integral T, size_t C, size_t R>
class list { 

  static constexpr size_t _Max = (C * R) / 2 - 2;
  std::array<std::pair<vec<T>, vec<T>>, _Max> _arr;
  using _vec_pair = decltype(_arr)::value_type; 

public:

  constexpr list(std::initializer_list<_vec_pair> list);

  constexpr operator bool() const { return _valid; }
  constexpr bool is_valid() const { return operator bool(); }

  constexpr size_t size() const { return _arr.size(); }

  constexpr auto to_abs_positions() const -> std::array<std::pair<T, T>, _Max>;

private:
  constexpr bool _check_vec(const vec<T>& vec) { return vec.x <= 0 || vec.x > C || vec.y <= 0 || vec.y > R; } 

  bool _valid;
}; 


template <std::integral T, size_t C, size_t R>
constexpr list<T, C, R>::list(std::initializer_list<_vec_pair> list) 
  : _arr{},
    _valid(false)
{ 
  std::ranges::copy(list, _arr.begin());
  
  // find the last position with a snake or ladder
  const auto _last_it = std::ranges::find_if(_arr, [](const _vec_pair& pair) { 
    return pair.first.is_null() && pair.second.is_null(); 
  }); 

  // zero out array if any of the vectors are out of bounds
  if ( !std::ranges::all_of(_arr.begin(), _last_it, [this](const _vec_pair& pair) { return _check_vec(pair.first) && _check_vec(pair.second); } ))
    std::ranges::fill(_arr, _vec_pair{});
  else
    _valid = true; 
}

template <std::integral T, size_t C, size_t R>
constexpr auto list<T, C, R>::to_abs_positions() const -> std::array<std::pair<T, T>, _Max> 
{  
  assert(is_valid() && "this list is not valid");  

  // 1. the code below first takes n elemenst which are not empty 
  // 2. decrements the vector parts (needed for converting to absolute distance, which begins at 0 not 1)
  // 3. sum the vectors coords together (first = first.x + first.y etc...)
  auto view = _arr 
  | std::ranges::views::take_while([](const _vec_pair& pair) {
    return !pair.first.is_null() || !pair.second.is_null(); 
  })
  | std::ranges::views::transform([](const _vec_pair& pair) {
    return _vec_pair( 
        { .x = pair.first.x -1, .y = pair.first.y -1}, 
        { .x = pair.second.x -1, .y = pair.second.y -1} 
      );
  })
  | std::ranges::views::transform([](const _vec_pair& pair) { 
    return std::pair<T, T>(
        pair.first.y * R + pair.first.x, 
        pair.second.y * R + pair.second.x
      );
  });  
 
  // copy view
  std::array<std::pair<T, T>, _Max> ret{};
  std::ranges::copy(view.begin(), view.end(), ret.begin()); 
  return ret;
}

} // snakes_and_ladders namespace 

#endif
