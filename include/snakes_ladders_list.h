#ifndef snakes_ladders_list_h 
#define snakes_ladders_list_h  

#include <assert.h>
#include <concepts>
#include <initializer_list>
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

  constexpr list(std::initializer_list<_vec_pair> inlist)
  : list( std::ranges::ref_view(inlist) )
  {}

  constexpr list(std::initializer_list<std::pair<T, T>> inlist)
  : list( std::ranges::ref_view(inlist) )
  {}

  // construct from cartesian coordinates
  template <std::ranges::input_range _R>
  requires std::same_as<std::ranges::range_value_t<_R>, std::pair<vec<T>, vec<T>>>
  constexpr list(_R&& r);
 
  // construct from absolute position-pairs
  template <std::ranges::input_range _R>
  requires std::same_as<std::ranges::range_value_t<_R>, std::pair<T, T>>
  constexpr list(_R&& r);

  constexpr operator bool() const { return _valid; }
  constexpr bool is_valid() const { return operator bool(); }

  constexpr size_t size() const { return _arr.size(); }

  constexpr auto to_absolute() const;

private:
  bool _valid;
}; 

template <std::integral T, size_t C, size_t R>
template <std::ranges::input_range _R>
requires std::same_as<std::ranges::range_value_t<_R>, std::pair<T, T>>
constexpr list<T, C, R>::list(_R&& r)
{
  // reconstruate the cartesian coordinates
  // The x = (coord % Cols) + 1, the y = (coord / Cols) + 1
  auto cartesian = r
    | std::views::take_while([](const auto& pair) 
      { return pair.first != 0 && pair.second != 0; }
    )
    | std::views::transform([](const auto& pair)
      { 
        const T o = pair.first;
        const T d = pair.second;
        const vec<T> o_vec = { .x = (o % C) +1, .y = (o / C) +1};
        const vec<T> d_vec = { .x = (d % C) +1, .y = (d / C) +1};
        return std::pair{ o_vec, d_vec };
      }
  );

  // let the other constr to the rest
  *this = cartesian;
}

template <std::integral T, size_t C, size_t R>
template <std::ranges::input_range _R>
requires std::same_as<std::ranges::range_value_t<_R>, std::pair<vec<T>, vec<T>>>
constexpr list<T, C, R>::list(_R&& r)
: _arr{},
  _valid( false )
{ 
  auto _invalid_vec = [](const vec<T>& vec) { return vec.x <= 0 || vec.x > C || vec.y <= 0 || vec.y > R; };

  // take a view until the last position with a snake or ladder (i.e. both vectors are null)
  // then check that none of the vectors until there are invalid 
  _valid =  std::ranges::none_of(
    r | std::views::take_while([](const _vec_pair& pair) 
      { return !pair.first.is_null() && !pair.second.is_null(); }),
    [&_invalid_vec](const _vec_pair& pair) 
      { return _invalid_vec(pair.first) || _invalid_vec(pair.second); }
  );

  if(_valid)
    std::ranges::copy(r, _arr.begin());
}

template <std::integral T, size_t C, size_t R>
constexpr auto list<T, C, R>::to_absolute() const
{
  assert(is_valid() && "this list is not valid");  

  // 1. the code below first takes n elemenst which are not empty 
  // 2. decrements the vector parts (needed for converting to absolute distance, which begins at 0 not 1)
  // 3. sum the vectors coords together (first = first.x + first.y etc...)
  return _arr 
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
}

} // snakes_and_ladders namespace 

#endif
