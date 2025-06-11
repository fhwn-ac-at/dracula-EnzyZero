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
class list : public std::array<std::pair<vec<T>, vec<T>>, (C * R) / 2 - 2> { 

  using _array = typename std::array<std::pair<vec<T>, vec<T>>, (C * R) / 2 - 2>;
  using _vec_pair = typename _array::value_type;

public:

  constexpr list(std::initializer_list<_vec_pair>& list);

  constexpr operator bool() const { return _valid; }
  constexpr bool is_valid() const { return operator bool(); }

  constexpr auto to_abs_positions() -> std::array<std::pair<T, T>, this->size()>;

private:
  bool _check_vec(vec<T>& vec) { return vec.x <= 0 || vec.x > C || vec.y <= 0 || vec.y > R; } 

  const _array::const_iterator _last_it;
  bool _valid;
}; 



template <std::integral T, size_t C, size_t R>
constexpr list<T, C, R>::list(std::initializer_list<_vec_pair>& list) 
  : _array( list ), 
  _last_it( std::ranges::find_if(*this, [](const _vec_pair& pair) { return pair.first.is_null() && pair.second.is_null(); }) ), 
  _valid(false)
{
  // zero out array if any of the vectors are out of bounds
  if ( !std::ranges::all_of(this->begin(), _last_it, [this](const _vec_pair& pair) { return _check_vec(pair.first) && _check_vec(pair.second); } ))
    std::ranges::fill(*this, {});
  else
    _valid = true;
}

template <std::integral T, size_t C, size_t R>
constexpr auto list<T, C, R>::to_abs_positions() -> std::array<std::pair<T, T>, this->size()> 
{  
  assert(is_valid() && "this list is not valid");  

  // 1. the code below first takes n elemenst which are not empty 
  // 2. decrements the vector parts (needed for converting to absolute distance, which begins at 0 not 1)
  // 3. sum the vectors coords together (first = first.x + first.y etc...)
  return *this
  | std::ranges::views::take_while([](const _vec_pair& pair) {
    return !pair.first.is_null() || !pair.second.is_null(); 
  })
  | std::ranges::views::transform([](const _vec_pair& pair) {
    return vec_pair( { .x = pair.first.x -1, .y = pair.first.y -1}, { .x = pair.second.x -1, .y = pair.second.y -1} );
  })
  | std::ranges::views::transform([](const _vec_pair& pair) { 
    return abs_pair(pair.first.y * R + pair.first.x, pair.second.y * R + pair.second.x);
  }); 
}

} // snakes_and_ladders namespace 

#endif
