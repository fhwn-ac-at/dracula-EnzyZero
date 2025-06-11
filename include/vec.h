#ifndef vec_h
#define vec_h 

#include <concepts>
 
template <std::integral T> 
struct vec {
  T x{}; 
  T y{};

  constexpr bool is_null() const { return y == 0 && x == 0; }
};

#endif
