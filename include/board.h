#ifndef board_h
#define board_h 

#include <initializer_list> 
#include <algorithm> 
#include <stdexcept> 
#include <concepts>
#include <array> 
#include <utility>

template <std::integral T, size_t C = 10, size_t R = 10>
class Board { 

public: 

  constexpr Board(const std::initializer_list<T>& list) 
  : _arr{}, _init(true)
  {
    std::copy(list.begin(), list.end(), _arr.begin());
  } 
 
  // may be used as a means to mark an error 
  constexpr Board() 
  : _arr{}, _init(false)
  {}  

  constexpr Board(Board& other) = default;
  constexpr Board& operator=(Board& other) = default;  

  constexpr Board(Board&& other) noexcept 
  : _arr( std::exchange(other._arr, {}) ), _init( std::exchange(other._init, false) )
  {}
   
  constexpr Board& operator=(Board&& other) noexcept {
    _arr  = std::exchange( other._arr, {});
    _init = std::exchange( other._init, false ); 
  } 

  constexpr operator bool() const noexcept { return _init; }    

  constexpr void valid(bool b) noexcept { _init = b; }
  constexpr bool valid() const noexcept { return operator bool(); }


  constexpr const T at(size_t x, size_t y) const { 

    if ( x <= 0 || x > C || y <= 0 || y > R)
      throw std::out_of_range("OUT::OF::RANGE access to board, coords are expected to be between 0 < v <= C or R");
 
    return _arr.at(R * y + x - 2);
  } 

  constexpr T& at(size_t x, size_t y) { 

    if ( x <= 0 || x > C || y <= 0 || y > R)
      throw std::out_of_range("OUT::OF::RANGE access to board, coords are expected to be between 0 < v <= C or R");
 
    return _arr.at(R * y + x - 2);
  } 

  /** 
   * @brief access absolute position in the array
   *
   * I.e. if the Board is 10x10, and board[50] is called, the 51st field will be accessed
  */
  constexpr const T operator[](size_t i) const noexcept { return _arr[i]; }
  constexpr T& operator[](size_t i) noexcept { return _arr[i]; } 

protected: 
  std::array<T, C * R> _arr;
  bool _init;
}; 
 

#endif
