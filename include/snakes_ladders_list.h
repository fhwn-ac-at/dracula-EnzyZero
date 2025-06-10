#ifndef snakes_ladders_list_h 
#define snakes_ladders_list_h  

#include "common.h"
#include <concepts>
#include <algorithm>
#include <array>
#include <utility>

namespace snakes_and_ladders {  

  template <std::size_t C, std::size_t R>
  inline constexpr std::size_t max = (C * R) / 2 - 2;
 
  namespace list { 

    template<std::integral T, std::size_t C, std::size_t R>
    using type = std::array<std::pair<cmn::vector<T>, cmn::vector<T>>, max<C, R>>;  

    template<std::integral T, std::size_t C, std::size_t R>
    consteval auto to_absolute_positions(type<T, C, R> list) ->std::array<std::pair<T, T>, max<C, R>> {  

      using abs_pair = std::pair<T, T>;
      using vector_pair = typename type<T, C, R>::value_type;

      std::array<abs_pair, max<C, R>> ret_arr;   

      auto view = list  

        // decrement the vector parts (needed for converting to absolute)
        | std::ranges::transform([](const auto& pair) {
            return vector_pair( { .x = pair.first.x -1, .y = pair.first.y -1}, { .x = pair.second.x -1, .y = pair.second.y -1} );
        })
        
        // now sum the vectors coords together (first = first.x + first.y etc...)
        | std::ranges::transform([](const auto& pair) { 
            return abs_pair(pair.first.y * R + pair.first.x, pair.second.y * R + pair.second.x);
        }); 
    
      // copy and return
      std::ranges::copy(view, ret_arr);
      return ret_arr;
    }

  } // list namespace
} // snakes_and_ladders namespace 

#endif
