#ifndef common_h
#define common_h 

#include <concepts>

namespace cmn {    
 
  // change this to use other integral type for board
  using board_int_t = unsigned;
  
  template <std::integral T> 
  struct vector {
    T x{}; 
    T y{};

    constexpr bool is_null() const { return y == 0 && x == 0; }
  };

} // cmn namespace 

#endif
