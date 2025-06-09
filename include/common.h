#ifndef common_h
#define common_h 

#include <array>
#include <concepts>

namespace cmn {    
 
  // change this to use other integral type for board
  using board_int_t = unsigned;
  
  template <std::integral T> 
  struct vector {
    T y;
    T x;
  };

  template<std::integral T, std::size_t C, std::size_t R>
  using snakes_and_ladders_list_t = std::array<std::pair< vector<T>, vector<T> >, (C * R) / 2 - 2>; 
 
  template<std::integral T, std::size_t F>
  using dice_weights_list_t = std::array<T, F>; 

  

} // cmn namespace 

#endif
