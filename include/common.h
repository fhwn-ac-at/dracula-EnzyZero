#ifndef common_h
#define common_h 

#include <array>

namespace common {
   
  template<std::size_t C, std::size_t R>
  using snakes_and_ladders_list_t = std::array<std::pair<unsigned, unsigned>, (C * R) / 2 - 2>; 
 
  template<std::size_t F>
  using dice_weights_list_t = std::array<unsigned, F>; 

  template<std::size_t C, std::size_t R>
  using board_t = std::array<unsigned, C * R>; 

} // common namespace 

#endif
