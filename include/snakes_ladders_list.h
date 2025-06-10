#ifndef snakes_ladders_list_h 
#define snakes_ladders_list_h  

#include <concepts>
#include <algorithm>
#include <ranges>
#include <array>
#include <utility> 

#include "common.h"

namespace snakes_and_ladders {  

  template <std::size_t C, std::size_t R>
  constexpr std::size_t max = (C * R) / 2 - 2;
 
  namespace list { 

    // TODO add descriptions
    template<std::integral T, std::size_t C, std::size_t R>
    using type = std::array<std::pair<cmn::vector<T>, cmn::vector<T>>, max<C, R>>;    

    template<std::integral T, std::size_t C, std::size_t R>
    constexpr bool is_valid(type<T, C, R> list);

    template<std::integral T, std::size_t C, std::size_t R>
    consteval auto to_absolute_positions(type<T, C, R> list) -> std::array<std::pair<T, T>, max<C, R>>;


    
    template<std::integral T, std::size_t C, std::size_t R>
    constexpr bool is_valid(type<T, C, R> list) { 

      using vec_pair = type<T, C, R>::value_type;

      // helper lambda
      auto check_vec = [](cmn::vector<T> vec) -> bool { return vec.x <= 0 || vec.x > C || vec.y <= 0 || vec.y > R; };

      // get an iterator to the first empty snake or ladder
      auto last_snake_or_ladder_it = std::ranges::find_if(list, [](const vec_pair& pair) { 
        return pair.first.is_null() && pair.second.is_null(); 
      });

      // check if any of the coordinates are out of range, abort baord if yes
      if (std::any_of(list.begin(), last_snake_or_ladder_it, [&check_vec](const vec_pair& pair) { return check_vec(pair.first) || check_vec(pair.second); })) 
        return false;

      return true;
    }

    template<std::integral T, std::size_t C, std::size_t R>
    consteval auto to_absolute_positions(type<T, C, R> list) -> std::array<std::pair<T, T>, max<C, R>> {  

      using abs_pair = std::pair<T, T>;
      using vec_pair = typename type<T, C, R>::value_type; // look at snakes_and_ladders::list::type 

      std::array<abs_pair, max<C, R>> ret_arr;   
 
      // 1. the code below first takes n elemenst which are not empty 
      // 2. decrements the vector parts (needed for converting to absolute distance, which begins at 0 not 1)
      // 3. sum the vectors coords together (first = first.x + first.y etc...)
      auto view = list
        | std::ranges::views::take_while([](const vec_pair& pair) {
            return !pair.first.is_null() || !pair.second.is_null(); 
        })
        | std::ranges::views::transform([](const vec_pair& pair) {
            return vec_pair( { .x = pair.first.x -1, .y = pair.first.y -1}, { .x = pair.second.x -1, .y = pair.second.y -1} );
        })
        | std::ranges::views::transform([](const vec_pair& pair) { 
            return abs_pair(pair.first.y * R + pair.first.x, pair.second.y * R + pair.second.x);
      }); 
    
      // copy and return
      std::ranges::copy(view, ret_arr.begin());
      return ret_arr;
    }

  } // list namespace 

} // snakes_and_ladders namespace 

#endif
